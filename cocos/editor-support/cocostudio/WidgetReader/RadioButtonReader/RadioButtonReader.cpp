

#include "editor-support/cocostudio/WidgetReader/RadioButtonReader/RadioButtonReader.h"

#include "ui/UIRadioButton.h"
#include "platform/CCFileUtils.h"
#include "2d/CCSpriteFrameCache.h"
#include "editor-support/cocostudio/CocoLoader.h"
#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/FlatBuffersSerialize.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
    static const char* P_BackGroundBoxData = "backGroundBoxData";
    static const char* P_BackGroundBoxSelectedData = "backGroundBoxSelectedData";
    static const char* P_FrontCrossData = "frontCrossData";
    static const char* P_BackGroundBoxDisabledData = "backGroundBoxDisabledData";
    static const char* P_FrontCrossDisabledData = "frontCrossDisabledData";
    
    static RadioButtonReader* instanceCheckBoxReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(RadioButtonReader)
    
        RadioButtonReader::RadioButtonReader()
    {
        
    }
    
    RadioButtonReader::~RadioButtonReader()
    {
        
    }
    
    RadioButtonReader* RadioButtonReader::getInstance()
    {
        if (!instanceCheckBoxReader)
        {
            instanceCheckBoxReader = new (std::nothrow) RadioButtonReader();
        }
        return instanceCheckBoxReader;
    }
    
    void RadioButtonReader::destroyInstance()
    {
        CC_SAFE_DELETE(instanceCheckBoxReader);
    }
    
    
    Offset<Table> RadioButtonReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                               flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        bool selectedState = false;
        bool displaystate = true;
        
        int backgroundboxResourceType = 0;
        std::string backgroundboxPath = "";
        std::string backgroundboxPlistFile = "";
        
        int backGroundBoxSelectedResourceType = 0;
        std::string backGroundBoxSelectedPath = "";
        std::string backGroundBoxSelectedPlistFile = "";
        
        int frontCrossResourceType = 0;
        std::string frontCrossPath = "";
        std::string frontCrossPlistFile = "";
        
        int backGroundBoxDisabledResourceType = 0;
        std::string backGroundBoxDisabledPath = "";
        std::string backGroundBoxDisabledPlistFile = "";
        
        
        int frontCrossDisabledResourceType = 0;
        std::string frontCrossDisabledPath = "";
        std::string frontCrossDisabledPlistFile = "";
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "CheckedState")
            {
                selectedState = (value == "True") ? true : false;
            }
            else if (name == "DisplayState")
            {
                displaystate = (value == "True") ? true : false;
            }
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "NormalBackFileData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        backgroundboxPath = value;
                    }
                    else if (name == "Type")
                    {
                        backgroundboxResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        backgroundboxPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (backgroundboxResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "PressedBackFileData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        backGroundBoxSelectedPath = value;
                    }
                    else if (name == "Type")
                    {
                        backGroundBoxSelectedResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        backGroundBoxSelectedPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (backGroundBoxSelectedResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "NodeNormalFileData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        frontCrossPath = value;
                    }
                    else if (name == "Type")
                    {
                        frontCrossResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        frontCrossPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (frontCrossResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "DisableBackFileData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        backGroundBoxDisabledPath = value;
                    }
                    else if (name == "Type")
                    {
                        backGroundBoxDisabledResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        backGroundBoxDisabledPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (backGroundBoxDisabledResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            else if (name == "NodeDisableFileData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        frontCrossDisabledPath = value;
                    }
                    else if (name == "Type")
                    {
                        frontCrossDisabledResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        frontCrossDisabledPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (frontCrossDisabledResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateRadioButtonOptions(*builder,
                                             widgetOptions,
                                             CreateResourceData(*builder,
                                                                builder->CreateString(backgroundboxPath),
                                                                builder->CreateString(backgroundboxPlistFile),
                                                                backgroundboxResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(backGroundBoxSelectedPath),
                                                                builder->CreateString(backGroundBoxSelectedPlistFile),
                                                                backGroundBoxSelectedResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(frontCrossPath),
                                                                builder->CreateString(frontCrossPlistFile),
                                                                frontCrossResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(backGroundBoxDisabledPath),
                                                                builder->CreateString(backGroundBoxDisabledPlistFile),
                                                                backGroundBoxDisabledResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(frontCrossDisabledPath),
                                                                builder->CreateString(frontCrossDisabledPlistFile),
                                                                frontCrossDisabledResourceType),
                                             selectedState,
                                             displaystate
                                             );
        
        return *(Offset<Table>*)&options;
    }
    
    void RadioButtonReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *radioButtonOptions)
    {
        auto options = (RadioButtonOptions*)radioButtonOptions;
        
        auto checkBox = static_cast<ui::RadioButton*>(node);
        
        //load background image
        bool backGroundFileExist = false;
        std::string backGroundErrorFilePath = "";
        auto backGroundDic = cocos2d::wext::makeResourceData(options->backGroundBoxData());
        int backGroundType = backGroundDic.type;
        std::string& backGroundTexturePath = backGroundDic.file;
        cocos2d::wext::onBeforeLoadObjectAsset(checkBox, backGroundDic, 0);
        switch (backGroundType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(backGroundTexturePath))
                {
                    backGroundFileExist = true;
                }
                else
                {
                    backGroundErrorFilePath = backGroundTexturePath;
                    backGroundFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = backGroundDic.plist;
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundTexturePath);
                if (spriteFrame)
                {
                    backGroundFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            backGroundErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        backGroundErrorFilePath = plist;
                    }
                    backGroundFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (backGroundFileExist)
        {
            checkBox->loadTextureBackGround(backGroundTexturePath, (Widget::TextureResType)backGroundType);
        }
        
        //load background selected image
        bool backGroundSelectedfileExist = false;
        std::string backGroundSelectedErrorFilePath = "";
        auto backGroundSelectedDic = cocos2d::wext::makeResourceData(options->backGroundBoxSelectedData());
        int backGroundSelectedType = backGroundSelectedDic.type;
        std::string& backGroundSelectedTexturePath = backGroundSelectedDic.file;
        cocos2d::wext::onBeforeLoadObjectAsset(checkBox, backGroundSelectedDic, 1);
        switch (backGroundSelectedType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(backGroundSelectedTexturePath))
                {
                    backGroundSelectedfileExist = true;
                }
                else
                {
                    backGroundSelectedErrorFilePath = backGroundSelectedTexturePath;
                    backGroundSelectedfileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = backGroundSelectedDic.plist;
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundSelectedTexturePath);
                if (spriteFrame)
                {
                    backGroundSelectedfileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            backGroundSelectedErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        backGroundSelectedErrorFilePath = plist;
                    }
                    backGroundSelectedfileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (backGroundSelectedfileExist)
        {
            checkBox->loadTextureBackGroundSelected(backGroundSelectedTexturePath, (Widget::TextureResType)backGroundSelectedType);
        }
        
        //load frontCross image
        bool frontCrossFileExist = false;
        std::string frontCrossErrorFilePath = "";
        auto frontCrossDic = cocos2d::wext::makeResourceData(options->frontCrossData());
        int frontCrossType = frontCrossDic.type;
        std::string& frontCrossFileName = frontCrossDic.file;
        cocos2d::wext::onBeforeLoadObjectAsset(checkBox, frontCrossDic, 2);
        switch (frontCrossType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(frontCrossFileName))
                {
                    frontCrossFileExist = true;
                }
                else
                {
                    frontCrossErrorFilePath = frontCrossFileName;
                    frontCrossFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = frontCrossDic.plist;
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frontCrossFileName);
                if (spriteFrame)
                {
                    frontCrossFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            frontCrossErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        frontCrossErrorFilePath = plist;
                    }
                    frontCrossFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (frontCrossFileExist)
        {
            checkBox->loadTextureFrontCross(frontCrossFileName, (Widget::TextureResType)frontCrossType);
        }
        
        //load backGroundBoxDisabledData
        bool backGroundBoxDisabledFileExist = false;
        std::string backGroundBoxDisabledErrorFilePath = "";
        auto backGroundDisabledDic = cocos2d::wext::makeResourceData(options->backGroundBoxDisabledData());
        int backGroundDisabledType = backGroundDisabledDic.type;
        std::string& backGroundDisabledFileName = backGroundDisabledDic.file;
        cocos2d::wext::onBeforeLoadObjectAsset(checkBox, backGroundDisabledDic, 3);
        switch (backGroundDisabledType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(backGroundDisabledFileName))
                {
                    backGroundBoxDisabledFileExist = true;
                }
                else
                {
                    backGroundBoxDisabledErrorFilePath = backGroundDisabledFileName;
                    backGroundBoxDisabledFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = backGroundDisabledDic.plist;
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundDisabledFileName);
                if (spriteFrame)
                {
                    backGroundBoxDisabledFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            backGroundBoxDisabledErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        backGroundBoxDisabledErrorFilePath = plist;
                    }
                    backGroundBoxDisabledFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (backGroundBoxDisabledFileExist)
        {
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName, (Widget::TextureResType)backGroundDisabledType);
        }
        
        ///load frontCrossDisabledData
        bool frontCrossDisabledFileExist = false;
        std::string frontCrossDisabledErrorFilePath = "";
        auto frontCrossDisabledDic = cocos2d::wext::makeResourceData(options->frontCrossDisabledData());
        int frontCrossDisabledType = frontCrossDisabledDic.type;
        std::string& frontCrossDisabledFileName = frontCrossDisabledDic.file;
        cocos2d::wext::onBeforeLoadObjectAsset(checkBox, frontCrossDisabledDic, 4);
        switch (frontCrossDisabledType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(frontCrossDisabledFileName))
                {
                    frontCrossDisabledFileExist = true;
                }
                else
                {
                    frontCrossDisabledErrorFilePath = frontCrossDisabledFileName;
                    frontCrossDisabledFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = frontCrossDisabledDic.plist;
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frontCrossDisabledFileName);
                if (spriteFrame)
                {
                    frontCrossDisabledFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            frontCrossDisabledErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        frontCrossDisabledErrorFilePath = plist;
                    }
                    frontCrossDisabledFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (frontCrossDisabledFileExist)
        {
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, (Widget::TextureResType)frontCrossDisabledType);
        }
        
        bool selectedstate = options->selectedState() != 0;
        checkBox->setSelected(selectedstate);
        
        bool displaystate = options->displaystate() != 0;
        checkBox->setBright(displaystate);
        checkBox->setEnabled(displaystate);
        
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
    }
    
    Node* RadioButtonReader::createNodeWithFlatBuffers(const flatbuffers::Table *checkBoxOptions)
    {
        auto radioButton = ui::RadioButton::create();// wext::aCheckBox();// CheckBox::create();
        
        setPropsWithFlatBuffers(radioButton, (Table*)checkBoxOptions);
        
        return radioButton;
    }

    int RadioButtonReader::getResourceType(std::string key)
    {
        if(key == "Normal" || key == "Default")
        {
            return 	0;
        }
        
        FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
        if(fbs->_isSimulator)
        {
            if(key == "MarkedSubImage")
            {
                return 0;
            }
        }
        return 1;
    }
}
