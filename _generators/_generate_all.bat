@set UINT8=--underlaying-type=std::uint8_t
@set UINT16=--underlaying-type=std::uint16_t
@set UINT32=--underlaying-type=std::uint32_t
@set INT=--underlaying-type=int

@set HEX2=--hex-width=2
@set HEX4=--hex-width=4
@set HEX6=--hex-width=6
@set HEX8=--hex-width=8

@rem set EXTRA=--enum-flags=extra
@rem same but more detailed
@set FLAGENUM_EXTRA=--enum-flags=serialize-set,deserialize-set

@set FLAGS=--enum-flags=flags
@set DECL=--enum-flags=type-decl
@set CLS=--enum-flags=enum-class
@set DECLCLS=--enum-flags=type-decl,enum-class
@set FMTHEX=--enum-flags=fmt-hex
@set SERIALIZE=--enum-flags=serialize,deserialize,lowercase

@set VALUES_CAMEL=--enum-values-style=CamelStyle
@set VALUES_PASCAL=--enum-values-style=PascalStyle 
@set SERIALIZE_PASCAL=--serialize-style=PascalStyle 


umba-enum-gen %EXTRA% %HEX6% %UINT32% -E=ColorRawEnum -F=@color_raw_enum.txt ..\color_raw_enum.h

@set TPL_OVERRIDE=--override-template-parameter=EnumNameFormat:$(ENAMNAME)
@set GEN_OPTS=--enum-values-style=CamelStyle

@rem flags,

@set ENDIANNESS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set ENDIANNESS_DEF=invalid,unknown=-1;littleEndian=0;bigEndian=1


@set HORALIGN_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set HORALIGN_DEF=invalid,alignInvalid=-1;left,alignLeft=0;center,alignCenter;right,alignRight;width,alignWidth;

@set VERTALIGN_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set VERTALIGN_DEF=invalid,alignInvalid=-1;top,alignTop=0;center,alignCenter;bottom,alignBottom

@set FONTSTYLEFLAGS_GEN_FLAGS=        --enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL% %FLAGENUM_EXTRA%
@set FONTSTYLEFLAGS_DEF=invalid=-1;normal,none=0;italic,oblique=1;underlined=2;strikeout=4;

@set GRADIENTROUNDRECTFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL% %FLAGENUM_EXTRA%
@set GRADIENTROUNDRECTFLAGS_DEF=invalid,unknown=-1;round,roundBoth,fillFull,none=0;squareBegin;squareEnd;noFillBegin;noFillEnd

@set FONTWEIGHT_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set FONTWEIGHT_DEF=invalid=-1;thin,100=100;extralight,ultralight,200=200;light,300=300;normal,400,regular=400;medium,500=500;semibold,600,demibold=600;bold,700=700;extrabold,800,ultrabold=800;heavy,900,black=900;

@set GRADIENTTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set GRADIENTTYPE_DEF=invalid,unknown=-1;vertical=0;horizontal;

@set LINETYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINETYPE_DEF=invalid,unknown=-1;diagonal=0;vertical;horizontal;

@set LINEDIRECTION_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINEDIRECTION_DEF=invalid,unknown=-1;fromLeftToRight,fromTopToBottom;fromRightToLeft,fromBottomToTop

@set LINEENDCAPSTYLE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINEENDCAPSTYLE_DEF=invalid,unknown=-1;round;square;flat,butt

@set LINEJOINSTYLE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINEJOINSTYLE_DEF=invalid,unknown=-1;bevel;mitter;round

@set BKMODE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set BKMODE_DEF=invalid,unknown=-1;transparent=1;opaque=2

@set ARCDIRECTION_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_PASCAL% %SERIALIZE_PASCAL%
@set ARCDIRECTION_DEF=invalid,unknown=-1;CounterClockwise,Ccw=1;Clockwise,Cw=2

@set SMOOTHINGMODE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set SMOOTHINGMODE_DEF=invalid,unknown=-1;defMode=0;highSpeed,lowQuality=1;highQuality,lowSpeed=2;noSmoothing,none=3;antiAlias=4

@set DRAWINGPRECISE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set DRAWINGPRECISE_DEF=invalid,unknown=-1;defPrecise=0;pixelPrecise;textPrecise;smoothingPrecise

@set DRAWTEXTFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL% %FLAGENUM_EXTRA% %HEX8%
@rem set DRAWTEXTFLAGS_DEF=invalid,unknown=-1;defMode=0;calcOnly=0x0001;fitGlyphEntire,fitGlyphDefault=0x0000;fitGlyphStartPos=0x0002;stopOnCr=0x0004;stopOnLf=0x0008;combiningAsSeparateGlyph,combiningAsGlyph=0x0010

@rem https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-sizing
@set WINDOWSIZINGEVENTEDGE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set WINDOWSIZINGEVENTEDGE_DEF=invalid,unknown=-1;none=0;left=1;right=2;top=3;topLeft=4;topRigh=5;bottom=6;bottomLeft=7;bottomRight=8

@rem https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-size
@set WINDOWSIZEREQUESTTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set WINDOWSIZEREQUESTTYPE_DEF=invalid,unknown=-1;restored,none=0;minimized=1;maximized=2;maxShow=3;maxHide=4;

@set MOUSEBUTTONEVENT_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set MOUSEBUTTONEVENT_DEF=invalid,unknown=-1;released=0;pressed=1;doubleClick=2

@set MOUSEBUTTON_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set MOUSEBUTTON_DEF=invalid,unknown=-1;none=0;leftButton;rightButton;middleButton,midButton;xButton1;xButton2

@set MOUSEBUTTONSTATEFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL% %FLAGENUM_EXTRA%
@set MOUSEBUTTONSTATEFLAGS_DEF=invalid,unknown=-1;none=0;leftButtonPressed=0x0001;rightButtonPressed=0x0002;shiftPressed=0x0004;controlPressed=0x0008;middleButtonPressed,midButtonPressed=0x0010;xButton1Pressed=0x0020;xButton2Pressed=0x0040

@set MOUSEMOVEEVENTTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@rem set MOUSEMOVEEVENTTYPE_DEF=invalid,unknown=-1;move=0;hover;leave;enter
@set MOUSEMOVEEVENTTYPE_DEF=invalid,unknown=-1;move=0;hover;leave

@set CALLBACKRESULTFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL% %FLAGENUM_EXTRA%
@set CALLBACKRESULTFLAGS_DEF=invalid,unknown=-1;none=0;repaint=1;captureMouse;releaseCapture;disableTimerUpdate;enableTimerUpdate


umba-enum-gen %GEN_OPTS% %HEX2% %TPL_OVERRIDE% ^
%ENDIANNESS_GEN_FLAGS%                  %UINT32% -E=Endianness                        -F=%ENDIANNESS_DEF%               ^
%HORALIGN_GEN_FLAGS%                    %UINT32% -E=HorAlign                         -F=%HORALIGN_DEF%               ^
%VERTALIGN_GEN_FLAGS%                   %UINT32% -E=VertAlign                        -F=%VERTALIGN_DEF%              ^
%FONTSTYLEFLAGS_GEN_FLAGS%              %UINT32% -E=FontStyleFlags                   -F=%FONTSTYLEFLAGS_DEF%         ^
%GRADIENTROUNDRECTFLAGS_GEN_FLAGS%      %UINT32% -E=GradientRoundRectFillFlags       -F=%GRADIENTROUNDRECTFLAGS_DEF% ^
%FONTWEIGHT_GEN_FLAGS%                  %INT% --enum-generation-flags=unsigned-vals  -E=FontWeight  -F=%FONTWEIGHT_DEF% ^
%GRADIENTTYPE_GEN_FLAGS%                %UINT32% -E=GradientType                     -F=%GRADIENTTYPE_DEF%           ^
%LINETYPE_GEN_FLAGS%                    %UINT32% -E=LineType                         -F=%LINETYPE_DEF% ^
%LINEDIRECTION_GEN_FLAGS%               %UINT32% -E=LineDirection                    -F=%LINEDIRECTION_DEF% ^
%LINEENDCAPSTYLE_GEN_FLAGS%             %UINT32% -E=LineEndcapStyle                  -F=%LINEENDCAPSTYLE_DEF% ^
%LINEJOINSTYLE_GEN_FLAGS%               %UINT32% -E=LineJoinStyle                    -F=%LINEJOINSTYLE_DEF% ^
%BKMODE_GEN_FLAGS%                      %UINT32% -E=BkMode                           -F=%BKMODE_DEF% ^
%ARCDIRECTION_GEN_FLAGS%                %UINT32% -E=ArcDirectionEnum                 -F=%ARCDIRECTION_DEF% ^
%SMOOTHINGMODE_GEN_FLAGS%               %UINT32% -E=SmoothingMode                    -F=%SMOOTHINGMODE_DEF% ^
%DRAWINGPRECISE_GEN_FLAGS%              %UINT32% -E=DrawingPrecise                   -F=%DRAWINGPRECISE_DEF% ^
%DRAWTEXTFLAGS_GEN_FLAGS%               %UINT32% -E=DrawTextFlags                    -F=@draw_text_flags.txt ^
%WINDOWSIZINGEVENTEDGE_GEN_FLAGS%       %UINT32% -E=WindowSizingEventEdge            -F=%WINDOWSIZINGEVENTEDGE_DEF% ^
%WINDOWSIZEREQUESTTYPE_GEN_FLAGS%       %UINT32% -E=WindowSizeRequestType            -F=%WINDOWSIZEREQUESTTYPE_DEF% ^
%MOUSEBUTTONEVENT_GEN_FLAGS%            %UINT32% -E=MouseButtonEvent                 -F=%MOUSEBUTTONEVENT_DEF% ^
%MOUSEBUTTON_GEN_FLAGS%                 %UINT32% -E=MouseButton                      -F=%MOUSEBUTTON_DEF% ^
%MOUSEBUTTONSTATEFLAGS_GEN_FLAGS%       %UINT32% -E=MouseButtonStateFlags            -F=%MOUSEBUTTONSTATEFLAGS_DEF% ^
%MOUSEMOVEEVENTTYPE_GEN_FLAGS%          %UINT32% -E=MouseMoveEventType               -F=%MOUSEMOVEEVENTTYPE_DEF% ^
%CALLBACKRESULTFLAGS_GEN_FLAGS%         %UINT32% -E=CallbackResultFlags              -F=%CALLBACKRESULTFLAGS_DEF% ^
..\draw_context_enums.h


@rem https://ru.wikipedia.org/wiki/Windows_Metafile
@rem PDF/DOCX - https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-emf/91c257d7-c39d-4a36-9b1f-63e3f73d30ca
@set NS_EMF=--namespace=marty_draw_context/emf
@set EMFRECORDTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%

@set EMFFORMATSIGNATURE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set EMFFORMATSIGNATURE_GEN_DEF=invalid,unknown=-1;emf=0x464D4520;eps=0x46535045

@set EMFOPENGLFLAG_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set EMFOPENGLFLAG_GEN_DEF=invalid,unknown=-1;openGlNotPresent,openGlAbsent=0;openGlPresent=1;

@set EMFMETAFILEHEADERSOPTION_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set EMFMETAFILEHEADERSOPTION_GEN_DEF=invalid,unknown=-1;basicHeader=0;headerExt1=1;headerExt2=2

@rem WinGDI.h:3159 - /* PIXELFORMATDESCRIPTOR flags */
@set EMFPIXELFORMATDESCRIPTORFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL% %FLAGENUM_EXTRA%
@set EMFPIXELFORMATDESCRIPTORFLAGS_GEN_DEF=invalid,unknown=-1;doubleBuffer=0x00000001;stereo=0x00000002;drawToWindow=0x00000004;drawToBitmap=0x00000008;supportGdi=0x00000010;supportOpenGl=0x00000020;genericFormat=0x00000040;needPalette=0x00000080;needSystemPalette=0x00000100;swapExchange=0x00000200;swapCopy=0x00000400;swapLayerBuffers=0x00000800;genericAccelerated=0x00001000;supportDirectDraw=0x00002000;direct3dAccelerated=0x00004000;supportComposition=0x00008000;depthDontCare=0x20000000;doubleBufferDontCare=0x40000000;stereoDontCare=0x80000000

@set EMFPFDPIXELTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set EMFPFDPIXELTYPE_GEN_DEF=invalid,unknown=-1;rgba=0;colorIndex=1


umba-enum-gen %GEN_OPTS% %UINT32% %HEX8% %TPL_OVERRIDE% %NS_EMF% ^
%EMFRECORDTYPE_GEN_FLAGS%                  -E=RecordType                 -F=@emf_record_type.txt ^
%EMFFORMATSIGNATURE_GEN_FLAGS%             -E=FormatSignature            -F=%EMFFORMATSIGNATURE_GEN_DEF% ^
%EMFOPENGLFLAG_GEN_FLAGS%                  -E=OpenGlPresenceFlag         -F=%EMFOPENGLFLAG_GEN_DEF% ^
%EMFMETAFILEHEADERSOPTION_GEN_FLAGS%       -E=MetafileHeaderOptions      -F=%EMFMETAFILEHEADERSOPTION_GEN_DEF% ^
%EMFPIXELFORMATDESCRIPTORFLAGS_GEN_FLAGS%  -E=PixelFormatDescriptorFlags -F=%EMFPIXELFORMATDESCRIPTORFLAGS_GEN_DEF% ^
%UINT8% %HEX2% ^
%EMFPFDPIXELTYPE_GEN_FLAGS%                -E=PfdPixelType               -F=%EMFPFDPIXELTYPE_GEN_DEF% ^
..\emf_enums.h


@set NS_SVG=--namespace=marty_draw_context/svg

@set SVGPATHSUBCOMMAND_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set SVGSHAPETYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex      %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set SVGTRANSFORMTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex  %VALUES_CAMEL% %SERIALIZE_PASCAL%

umba-enum-gen %GEN_OPTS% %UINT32% %HEX8% %TPL_OVERRIDE% %NS_SVG% ^
%SVGPATHSUBCOMMAND_GEN_FLAGS%              -E=PathSubcommand             -F=@svg_path_subcommand.txt ^
%SVGSHAPETYPE_GEN_FLAGS%                   -E=ShapeType                  -F=@svg_shape_type.txt ^
%SVGTRANSFORMTYPE_GEN_FLAGS%               -E=TransformType              -F=@svg_transform_type.txt ^
..\svg_enums.h

