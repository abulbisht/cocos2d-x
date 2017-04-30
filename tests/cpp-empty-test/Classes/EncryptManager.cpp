
#include <stdio.h>
#include <string>

#include "crypto-support/crypto_wrapper.h"

#include "cocos2d.h"

#include "platform/win32/CCFileUtils-win32.h"
#include "platform/android/CCFileUtils-android.h"
#include "platform/winrt/CCFileUtilsWinRT.h"

#include "EncryptManager.h"
#include "crypto-support/nsconv.h"
#include "crypto-support/fastest_csv_parser.h"
#include "crypto-support/ibinarystream.h"

using namespace cocos2d;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
typedef FileUtilsWin32 FileUtilsImpl;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
typedef FileUtilsAndroid FileUtilsImpl;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
typedef CCFileUtilsWinRT FileUtilsImpl;
#else /* ios or mac */
typedef public FileUtils FileUtilsImpl;
#endif

class FileUtilsNoEncrypt : public FileUtilsImpl
{
};

class FileUtilsEncrypt : public FileUtilsImpl
{
public:
    FileUtilsEncrypt(EncryptManager& manager) : encryptManager(manager)
    {
    }

    /**
    *  Gets string from a file.
    */
    std::string getStringFromFile(const std::string& filename) override
    {
        auto data = FileUtilsImpl::getStringFromFile(filename);
        crypto::aes::decrypt(data, encryptManager._encryptKey.c_str());
        return crypto::zlib::uncompress(data);
    }

    /**
    *  Creates binary data from a file.
    *  @return A data object.
    */
    Data getDataFromFile(const std::string& filename) override
    {
        auto data = FileUtilsImpl::getDataFromFile(filename);

        size_t size = 0;
        crypto::aes::privacy::mode_spec<>::decrypt(data.getBytes(), data.getSize(), data.getBytes(), size, encryptManager._encryptKey.c_str());

        // auto uncompr = crypto::zlib::uncompress(unmanaged_string((const char*)data.getBytes(), size));

        auto uncomprData = crypto::zlib::abi::_inflate(unmanaged_string((const char*)data.getBytes(), size));
        size = uncomprData.size();

        data.clear();

        data.fastSet((unsigned char*)uncomprData.deatch(), size);

        return data;
    }

    /**
    *  Gets resource file data
    *
    *  @param[in]  filename The resource file name which contains the path.
    *  @param[in]  mode The read mode of the file.
    *  @param[out] size If the file read operation succeeds, it will be the data size, otherwise 0.
    *  @return Upon success, a pointer to the data is returned, otherwise NULL.
    *  @warning Recall: you are responsible for calling free() on any Non-NULL pointer returned.
    */
    virtual unsigned char* getFileData(const std::string& filename, const char* mode, ssize_t *size) override
    {
        auto data = FileUtilsImpl::getFileData(filename, mode, size);

        size_t outsize = 0;
        crypto::aes::privacy::mode_spec<>::decrypt(data, *size, data, outsize, encryptManager._encryptKey.c_str());

        auto uncomprData = crypto::zlib::abi::_inflate(unmanaged_string((const char*)data, outsize));
        *size = uncomprData.size();

        free(data);

        return (unsigned char*)uncomprData.deatch();
    }

    std::string fullPathForFilename(const std::string &filename) const override
    {
        auto iter = encryptManager._indexFileMap.find(filename);
        if (iter != encryptManager._indexFileMap.end())
            return iter->second;

        return FileUtilsImpl::fullPathForFilename(filename);
    }

    EncryptManager& encryptManager;
};

EncryptManager* EncryptManager::getInstance()
{
    static EncryptManager s_EncryptManager;
    return &s_EncryptManager;
}

void EncryptManager::setEncryptEnabled(bool bVal, const std::string& key, const std::string& ivec)
{
    if (bVal && !key.empty()) {
        _encryptKey.clear();
        _encryptIvec.clear();

        _encryptKey.resize(32);
        int keysize = key.size();
        if (keysize > 32)
            keysize = 32;

        ::memcpy(&_encryptKey.front(), key.c_str(), keysize);

        if (!ivec.empty()) {
            _encryptIvec.resize(16);
            ::memcpy(&_encryptIvec.front(), ivec.c_str(), (std::min)(16, (int)ivec.size()));
        }
        else {
            _encryptIvec = nsc::hex2bin("00234b89aa96fecdaf80fbf178a25621");
        }

        crypto::aes::detail::set_ivec(_encryptIvec.c_str());

        setupHookFuncs();
        _encryptEnabled = bVal;
    }
    else {
        auto fileUtilsNoEncrypt = new FileUtilsNoEncrypt();
        fileUtilsNoEncrypt->init();
        FileUtils::setDelegate(fileUtilsNoEncrypt);

        _encryptEnabled = false;
    }
}

void EncryptManager::setupHookFuncs()
{
    auto fileUtilsEncrypt = new FileUtilsEncrypt(*this);
    fileUtilsEncrypt->init();
    FileUtils::setDelegate(fileUtilsEncrypt);

    auto fileUtils = FileUtils::getInstance();

    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    cocos2d::log("Writable Path:%s", writablePath.c_str());
    FileUtils::getInstance()->addSearchPath(writablePath, true);
}

void EncryptManager::enableFileIndex(const std::string& indexFile, FileIndexFormat format)
{
    this->_indexFileMap.clear();

    auto buffer = FileUtils::getInstance()->getStringFromFile(indexFile);
    if (format == FileIndexFormat::Binary)
    {
        int fileCount = 0;
        ibinarystream ibs(buffer.c_str(), buffer.size());
        ibs.read_i(fileCount);
        for (auto i = 0; i < fileCount; ++i)
        {
            std::string key, value;
            ibs.read_v(key);
            ibs.read_v(value);
            this->_indexFileMap.emplace(std::move(key), std::move(value));
        }
    }
    else if (format == FileIndexFormat::Csv)
    {
        const char* endl = buffer.c_str();
        const char* cursor = nullptr;
        do {
            std::string key, value;
            cursor = endl;
            auto counter = 0;
            endl = fastest_csv_parser::csv_parse_line(cursor, [&](const char* v_start, const char* v_end) {
                if (counter == 0)
                {
                    key.assign(v_start, v_end - v_start);
                }
                else {
                    value.assign(v_start, v_end - v_start);
                }
                ++counter;
            });

            _indexFileMap.emplace(std::move(key), std::move(value));
        } while ((endl - buffer.c_str()) < buffer.size());
    }
}
