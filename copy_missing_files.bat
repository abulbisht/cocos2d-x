@echo off

xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\SpineSkeletonReader"  "frameworks\cocos2d-x\cocos\editor-support\cocostudio\WidgetReader\SpineSkeletonReader\"
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\RichTextReader"  "frameworks\cocos2d-x\cocos\editor-support\cocostudio\WidgetReader\RichTextReader\"
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\ControlSwitchReader"  "frameworks\cocos2d-x\cocos\editor-support\cocostudio\WidgetReader\ControlSwitchReader\"
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\RadioButtonReader"  "frameworks\cocos2d-x\cocos\editor-support\cocostudio\WidgetReader\RadioButtonReader\"

copy /y "%COCOS2DX_ROOT%\cocos\editor-support\spine\SpineSkeletonCache.*"  "frameworks\cocos2d-x\cocos\editor-support\spine\"

copy /y "%COCOS2DX_ROOT%\cocos\2d\libxreader*"  "frameworks\cocos2d-x\cocos\2d\"
copy /y "%COCOS2DX_ROOT%\cocos\2d\resource.h"  "frameworks\cocos2d-x\cocos\2d\"
copy /y "%COCOS2DX_ROOT%\external\glfw3\include\win32\glfw3ext.h" "frameworks\cocos2d-x\external\glfw3\include\win32\glfw3ext.h"

rem copy dragonBones
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\dragonBones"  "frameworks\cocos2d-x\cocos\editor-support\dragonBones\"

rem xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\reader21"  "frameworks\cocos2d-x\cocos\editor-support\reader21"

ping /n 2 127.0.1>nul && goto :eof
