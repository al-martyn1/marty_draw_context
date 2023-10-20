@set UINT8=--underlaying-type=std::uint8_t
@set UINT16=--underlaying-type=std::uint16_t
@set UINT32=--underlaying-type=std::uint32_t
@set INT=--underlaying-type=int

@set HEX2=--hex-width=2
@set HEX4=--hex-width=4
@set HEX6=--hex-width=6
@set HEX8=--hex-width=8

@rem set EXTRA=--enum-flags=extra
@same but more detailed
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
@set HORALIGN_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex
@set HORALIGN_DEF=invalid,alignInvalid=-1;left,alignLeft=0;center,alignCenter;right,alignRight;width,alignWidth;

@set VERTALIGN_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex
@set VERTALIGN_DEF=invalid,alignInvalid=-1;top,alignTop=0;center,alignCenter;bottom,alignBottom

@set FONTSTYLEFLAGS_GEN_FLAGS=        --enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %FLAGENUM_EXTRA%
@set FONTSTYLEFLAGS_DEF=invalid=-1;normal,none=0;italic=1;underlined=2;strikeout=4;

@set GRADIENTROUNDRECTFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %FLAGENUM_EXTRA%
@set GRADIENTROUNDRECTFLAGS_DEF=invalid,unknown=-1;round,roundBoth,fillFull,none=0;squareBegin;squareEnd;noFillBegin;noFillEnd

@set FONTWEIGHT_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class
@set FONTWEIGHT_DEF=invalid=-1;thin,100=100;extralight,ultralight,200=200;light,300=300;normal,400,regular=400;medium,500=500;semibold,600,demibold=600;bold,700=700;extrabold,800,ultrabold=800;heavy,900,black=900;

@set GRADIENTTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex
@set GRADIENTTYPE_DEF=invalid,unknown=-1;vertical=0;horizontal;

@set LINETYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINETYPE_DEF=invalid,unknown=-1;diagonal=0;vertical;horizontal;

@set LINEDIRECTION_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINEDIRECTION_DEF=invalid,unknown=-1;fromLeftToRight,fromTopToBottom;fromRightToLeft,fromBottomToTop

@set LINEENDCAPSTYLE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINEENDCAPSTYLE_DEF=invalid,unknown=-1;round;square;flat

@set LINEJOINSTYLE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set LINEJOINSTYLE_DEF=invalid,unknown=-1;bevel;mitter;round

@set BKMODE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set BKMODE_DEF=invalid,unknown=-1;opaque;transparent

@set ARCDIRECTION_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_PASCAL% %SERIALIZE_PASCAL%
@set ARCDIRECTION_DEF=invalid,unknown=-1;Cw,Clockwise;Ccw,CounterClockwise

@set SMOOTHINGMODE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set SMOOTHINGMODE_DEF=invalid,unknown=-1;defMode=0;highSpeed,lowQuality=1;highQuality,lowSpeed=2;noSmoothing,none=3;antiAlias=4

@set DRAWINGPRECISE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class %VALUES_CAMEL% %SERIALIZE_PASCAL%
@set DRAWINGPRECISE_DEF=invalid,unknown=-1;defPrecise=0;pixelPrecise;textPrecise;smoothingPrecise

@set DRAWTEXTFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex %FLAGENUM_EXTRA% %HEX8%
@rem set DRAWTEXTFLAGS_DEF=invalid,unknown=-1;defMode=0;calcOnly=0x0001;fitGlyphEntire,fitGlyphDefault=0x0000;fitGlyphStartPos=0x0002;stopOnCr=0x0004;stopOnLf=0x0008;combiningAsSeparateGlyph,combiningAsGlyph=0x0010


umba-enum-gen %GEN_OPTS% %HEX2% %TPL_OVERRIDE% ^
%HORALIGN_GEN_FLAGS%                %UINT32% -E=HorAlign                         -F=%HORALIGN_DEF%               ^
%VERTALIGN_GEN_FLAGS%               %UINT32% -E=VertAlign                        -F=%VERTALIGN_DEF%              ^
%FONTSTYLEFLAGS_GEN_FLAGS%          %UINT32% -E=FontStyleFlags                   -F=%FONTSTYLEFLAGS_DEF%         ^
%GRADIENTROUNDRECTFLAGS_GEN_FLAGS%  %UINT32% -E=GradientRoundRectFillFlags       -F=%GRADIENTROUNDRECTFLAGS_DEF% ^
%FONTWEIGHT_GEN_FLAGS%              %INT% --enum-generation-flags=unsigned-vals  -E=FontWeight  -F=%FONTWEIGHT_DEF% ^
%GRADIENTTYPE_GEN_FLAGS%            %UINT32% -E=GradientType                     -F=%GRADIENTTYPE_DEF%           ^
%LINETYPE_GEN_FLAGS%                %UINT32% -E=LineType                         -F=%LINETYPE_DEF% ^
%LINEDIRECTION_GEN_FLAGS%           %UINT32% -E=LineDirection                    -F=%LINEDIRECTION_DEF% ^
%LINEENDCAPSTYLE_GEN_FLAGS%         %UINT32% -E=LineEndcapStyle                  -F=%LINEENDCAPSTYLE_DEF% ^
%LINEJOINSTYLE_GEN_FLAGS%           %UINT32% -E=LineJoinStyle                    -F=%LINEJOINSTYLE_DEF% ^
%BKMODE_GEN_FLAGS%                  %UINT32% -E=BkMode                           -F=%BKMODE_DEF% ^
%ARCDIRECTION_GEN_FLAGS%            %UINT32% -E=ArcDirectionEnum                 -F=%ARCDIRECTION_DEF% ^
%SMOOTHINGMODE_GEN_FLAGS%           %UINT32% -E=SmoothingMode                    -F=%SMOOTHINGMODE_DEF% ^
%DRAWINGPRECISE_GEN_FLAGS%          %UINT32% -E=DrawingPrecise                   -F=%DRAWINGPRECISE_DEF% ^
%DRAWTEXTFLAGS_GEN_FLAGS%           %UINT32% -E=DrawTextFlags                    -F=@draw_text_flags.txt ^
..\draw_context_enums.h

