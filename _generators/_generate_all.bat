@set UINT8=--underlaying-type=std::uint8_t
@set UINT16=--underlaying-type=std::uint16_t
@set UINT32=--underlaying-type=std::uint32_t
@set INT=--underlaying-type=int

@set HEX2=--hex-width=2
@set HEX4=--hex-width=4
@set HEX6=--hex-width=6
@set HEX8=--hex-width=8

@set EXTRA=--enum-flags=extra
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
@set HORALIGN_DEF=invalid,alignInvalid=-1;left,alignLeft=0;center,alignCenter;right,alignRight;

@set FONTSTYLEFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex,extra
@set FONTSTYLEFLAGS_DEF=invalid=-1;normal,none=0;italic=1;underlined=2;strikeout=4;

@set FONTWEIGHT_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class
@set FONTWEIGHT_DEF=invalid=-1;thin,100=100;extralight,ultralight,200=200;light,300=300;normal,400,regular=400;medium,500=500;semibold,600,demibold=600;bold,700=700;extrabold,800,ultrabold=800;heavy,900,black=900;

@set GRADIENTTYPE_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,fmt-hex
@set GRADIENTTYPE_DEF=invalid,unknown=-1;vertical=0;horizontal;

@set GRADIENTROUNDRECTFLAGS_GEN_FLAGS=--enum-flags=0 --enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,flags,fmt-hex
@set GRADIENTROUNDRECTFLAGS_DEF=invalid,unknown=-1;round,roundBoth,fillFull,none=0;squareBegin;squareEnd;noFillBegin;noFillEnd

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



umba-enum-gen %GEN_OPTS% %HEX2% %TPL_OVERRIDE% ^
%HORALIGN_GEN_FLAGS%                %UINT32% -E=HorAlign                         -F=%HORALIGN_DEF%               ^
%FONTSTYLEFLAGS_GEN_FLAGS%          %UINT32% -E=FontStyleFlags                   -F=%FONTSTYLEFLAGS_DEF%         ^
%FONTWEIGHT_GEN_FLAGS%              %INT% --enum-generation-flags=unsigned-vals  -E=FontWeight  -F=%FONTWEIGHT_DEF% ^
%GRADIENTTYPE_GEN_FLAGS%            %UINT32% -E=GradientType                     -F=%GRADIENTTYPE_DEF%           ^
%GRADIENTROUNDRECTFLAGS_GEN_FLAGS%  %UINT32% -E=GradientRoundRectFillFlags       -F=%GRADIENTROUNDRECTFLAGS_DEF% ^
%LINETYPE_GEN_FLAGS%                %UINT32% -E=LineType                         -F=%LINETYPE_DEF% ^
%LINEDIRECTION_GEN_FLAGS%           %UINT32% -E=LineDirection                    -F=%LINEDIRECTION_DEF% ^
%LINEENDCAPSTYLE_GEN_FLAGS%         %UINT32% -E=LineEndcapStyle                  -F=%LINEENDCAPSTYLE_DEF% ^
%LINEJOINSTYLE_GEN_FLAGS%           %UINT32% -E=LineJoinStyle                    -F=%LINEJOINSTYLE_DEF% ^
%BKMODE_GEN_FLAGS%                  %UINT32% -E=BkMode                           -F=%BKMODE_DEF% ^
%ARCDIRECTION_GEN_FLAGS%            %UINT32% -E=ArcDirectionEnum                 -F=%ARCDIRECTION_DEF% ^
..\draw_context_enums.h

