#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct DrawingColor : public ColorRef
{

    DrawingColor() : ColorRef() {}

    DrawingColor(ColorRef clr) : ColorRef(clr) {}
    DrawingColor(const DrawingColor &clr) : ColorRef(clr) {}
    DrawingColor(DrawingColor &&clr)      : ColorRef(clr) {}

    DrawingColor& operator=(ColorRef clr)
    {
        r = clr.r;
        g = clr.g;
        b = clr.b;
        a = clr.a;
        return *this;
    }

    DrawingColor& operator=(const DrawingColor &clr) = default;
    DrawingColor& operator=(DrawingColor &&clr) = default;


    operator marty_draw_context::ColorRef() const
    {
        return (ColorRef)*this;
    }

    explicit operator std::uint32_t() const
    {
        return toUnsigned();
    }

    static
    DrawingColor fromString(const ssq::Class&, const ssq::sqstring &colorName)
    {
        try
        {
            #if !defined(SQUNICODE)

                return (DrawingColor)ColorRef::deserialize(colorName);

            #else

                std::string colorNameAscii = marty_simplesquirrel::to_ascii(colorName);
                return (DrawingColor)ColorRef::deserialize(colorNameAscii);

            #endif
        }
        catch(...)
        {
        }

        return DrawingColor();
    }

    static
    DrawingColor fromUnsignedBindHelper( const ssq::Class&, std::uint32_t uclr )
    {
        return (DrawingColor)ColorRef::fromUnsigned(uclr);
    }

    static
    DrawingColor fromIntBindHelper( const ssq::Class&, int iclr )
    {
        return (DrawingColor)ColorRef::fromUnsigned((std::uint32_t)(std::int32_t)iclr);
    }

    static
    DrawingColor fromRgb( const ssq::Class&, int r, int g, int b )
    {
        ColorRef clr;

        clr.r = (std::uint8_t)(std::uint32_t)r;
        clr.g = (std::uint8_t)(std::uint32_t)g;
        clr.b = (std::uint8_t)(std::uint32_t)b;

        clr.a = 0;

        return (DrawingColor)clr;
    }

    int toIntBindHelper() const
    {
        return (int)(std::int32_t)toUnsigned();
    }

    float toFloatBindHelper() const
    {
        return (float)(std::int32_t)toUnsigned();
    }

    static
    marty_simplesquirrel::ClassInfo getClassInfo(const std::string &clsName = "Color")
    {
        auto clsInfo = marty_simplesquirrel::ClassInfo(clsName);

        //clsInfo.addFunc("integer len() const");
        //clsInfo.addMember("table{ string name -> string value } env");
        //clsInfo.addClass( BinaryData                    ::getClassInfo() );

        //clsInfo.addFunc("constuctor(any_integral intValOrName)");
        clsInfo.addConstructor("integer|float|string|array of integer[r,g,b,a]|Drawing.Color clrInit");

        clsInfo.addFunc("static Drawing.Color fromRgb(integer r, integer g, integer b)");
        clsInfo.addFunc("static Drawing.Color fromUnsigned(integer u)");
        clsInfo.addFunc("static Drawing.Color fromInt(integer u)");
        clsInfo.addFunc("static Drawing.Color fromInteger(integer u)");
        clsInfo.addFunc("static Drawing.Color fromString(string nameOrIntStr)");

        clsInfo.addFunc("integer toUnsigned() const");
        clsInfo.addFunc("integer toInt() const");
        //clsInfo.addFunc("integer toInteger() const");
        clsInfo.addFunc("integer tointeger() const");

        //clsInfo.addFunc("float toFloat() const");
        clsInfo.addFunc("float tofloat() const");

        //clsInfo.addFunc("string toString() const");
        clsInfo.addFunc("string tostring() const");
        clsInfo.addFunc("string _tostring() const");


        clsInfo.addMember("integer r");
        clsInfo.addMember("integer g");
        clsInfo.addMember("integer b");
        clsInfo.addMember("integer a");

        return clsInfo;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("Color"))
    {
        const bool staticMethod = true ;
        //const bool classMethod  = false;

        auto cls = vm.addClass( className.c_str()
                              , [](ssq::Object o) -> DrawingColor*
                                {
                                    if (o.isNull() || o.isEmpty())
                                    {
                                        return new DrawingColor();
                                    }

                                    ssq::Type t = o.getType();
                                    switch(t)
                                    {
                                        case ssq::Type::INTEGER:
                                            return new DrawingColor((DrawingColor)ColorRef::fromUnsigned((std::uint32_t)(std::int32_t)o.toInt()));
                                
                                        case ssq::Type::FLOAT:
                                            return new DrawingColor((DrawingColor)ColorRef::fromUnsigned((std::uint32_t)(std::int32_t)(0.5+o.toFloat())));
                                
                                        case ssq::Type::STRING:
                                            return new DrawingColor(fromString(ssq::Class(), o.toString()));

                                        case ssq::Type::ARRAY:
                                        {
                                            std::vector<int> rgbaVec = marty_simplesquirrel::fromArrayObjectToVectorConvert<int>(o, _SC("val"), false /* allowSingleVal */ );
                                            while(rgbaVec.size()<4)
                                            {
                                                rgbaVec.emplace_back(0);
                                            }

                                            ColorRef colorRef;
                                            colorRef.r = (std::uint8_t)(unsigned)rgbaVec[0];
                                            colorRef.g = (std::uint8_t)(unsigned)rgbaVec[1];
                                            colorRef.b = (std::uint8_t)(unsigned)rgbaVec[2];
                                            colorRef.a = (std::uint8_t)(unsigned)rgbaVec[3];
                                            return new DrawingColor(colorRef);
                                        }

                                        case ssq::Type::INSTANCE:
                                        {
                                            try
                                            {
                                                return new DrawingColor(o.to<DrawingColor>());
                                            }
                                            catch(...)
                                            {
                                            }
                                        }
                                        [[fallthrough]];

                                        case ssq::Type::BOOL:
                                        case ssq::Type::NULLPTR:
                                        case ssq::Type::TABLE:
                                        //case ssq::Type::ARRAY:
                                        case ssq::Type::USERDATA:
                                        case ssq::Type::CLOSURE:
                                        case ssq::Type::NATIVECLOSURE:
                                        case ssq::Type::GENERATOR:
                                        case ssq::Type::USERPOINTER:
                                        case ssq::Type::THREAD:
                                        case ssq::Type::FUNCPROTO:
                                        //case ssq::Type::INSTANCE:
                                        case ssq::Type::CLASS:
                                        case ssq::Type::WEAKREF:
                                        case ssq::Type::OUTER:
                                            [[fallthrough]];
                                        default: {}
                                    }

                                    return new DrawingColor();
                                }
                              , true // release
                              );


        cls.addFunc( _SC("fromRgb")     , &DrawingColor::fromRgb);

        cls.addFunc( _SC("toUnsigned")  , &DrawingColor::toUnsigned);
        cls.addFunc( _SC("fromUnsigned"), &DrawingColor::fromUnsignedBindHelper);

        cls.addFunc( _SC("toInt")       , &DrawingColor::toIntBindHelper);
        cls.addFunc( _SC("toInteger")   , &DrawingColor::toIntBindHelper);
        cls.addFunc( _SC("tointeger")   , &DrawingColor::toIntBindHelper);

        cls.addFunc( _SC("toFloat")     , &DrawingColor::toFloatBindHelper);
        cls.addFunc( _SC("tofloat")     , &DrawingColor::toFloatBindHelper);

        cls.addFunc( _SC("fromInt")     , &DrawingColor::fromIntBindHelper, staticMethod);
        cls.addFunc( _SC("fromInteger") , &DrawingColor::fromIntBindHelper, staticMethod);

        cls.addFunc( _SC("fromString")  , &DrawingColor::fromString);
        cls.addFunc( _SC("toString")
                   , [](DrawingColor* self) -> ssq::sqstring
                     {
                         MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                         return marty_simplesquirrel::to_sqstring(self->serialize());
                     }
                   );
        cls.addFunc( _SC("tostring")
                   , [](DrawingColor* self) -> ssq::sqstring
                     {
                         MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                         return marty_simplesquirrel::to_sqstring(self->serialize());
                     }
                   );

        cls.addFunc( _SC("_tostring")
                   , [](DrawingColor* self) -> ssq::sqstring
                     {
                         MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                         return marty_simplesquirrel::to_sqstring(self->serialize());
                     }
                   );


        cls.addVar(_SC("r")     , &DrawingColor::r);
        cls.addVar(_SC("g")     , &DrawingColor::g);
        cls.addVar(_SC("b")     , &DrawingColor::b);
        cls.addVar(_SC("a")     , &DrawingColor::a);


        // алиасы с динными именами для r/g/b
        // может, не делать с длинными именами?
        // может, стоит сделать кучу статиков-алисов для именованных цветов?

        // Пока не буду добавлять
        // cls.addVar(_SC("red")   , &DrawingColor::r);
        // cls.addVar(_SC("green") , &DrawingColor::g);
        // cls.addVar(_SC("blue")  , &DrawingColor::b);
        // cls.addVar(_SC("alpha") , &DrawingColor::a);

        return cls;
    }


}; // struct DrawingColor



} // namespace simplesquirrel {
} // namespace marty_draw_context {

