#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct DrawingCoords
{
    float x;
    float y;

    DrawingCoords() : x(0.0), y(0.0) {}
    DrawingCoords(float x_, float y_) : x(x_), y(y_) {}
    DrawingCoords(const DrawCoord &c) : x(floatToFloat(c.x)), y(floatToFloat(c.y)) {}
    DrawingCoords(const DrawingCoords &c) : x(c.x), y(c.y) {}
    DrawingCoords(DrawingCoords&&) = default;

    DrawingCoords& operator=(const DrawingCoords &c) = default;
    DrawingCoords& operator=(DrawingCoords &&) = default;

    DrawingCoords& operator=(const DrawCoord &c)
    {
        x = floatToFloat(c.x);
        y = floatToFloat(c.y);
        return *this;
    }

    operator marty_draw_context::DrawCoord() const
    {
        marty_draw_context::DrawCoord res;
        res.x = (marty_draw_context::DrawCoord::value_type)x;
        res.y = (marty_draw_context::DrawCoord::value_type)y;
        return res;
    }

    DrawingCoords addImpl(DrawingCoords c)
    {
        return DrawingCoords(x+c.x, y+c.y);
    }

    DrawingCoords subImpl(DrawingCoords c)
    {
        return DrawingCoords(x-c.x, y-c.y);
    }

    DrawingCoords unmImpl()
    {
        return DrawingCoords(-x, -y);
    }

    DrawingCoords mulImpl(DrawingCoords c)
    {
        return DrawingCoords(x*c.x, y*c.y);
    }

    DrawingCoords divImpl(DrawingCoords c)
    {
        //RuntimeException(const char* msg, const char* source, const char* func, int line):Exception(msg) {
        if (c.x==0 || c.y==0)
        {
            throw ssq::RuntimeException( c.x==0 ? "division by zero (DrawingCoords.x)" : "division by zero (DrawingCoords.y)"
                                       , "somehere in '.nut' files"
                                       , "DrawingCoords._div"
                                       , 0
                                       );
        }

        return DrawingCoords(x/c.x, y/c.y);
    }

    ssq::sqstring toString() const
    {
        return marty_simplesquirrel::to_sqstring(
            marty_draw_context::floatToString(x) + 
            std::string(",")                     +
            marty_draw_context::floatToString(x) 
        );
    }

    static
    marty_simplesquirrel::ClassInfo getClassInfo(const std::string &clsName = "Coords")
    {
        auto clsInfo = marty_simplesquirrel::ClassInfo(clsName);

        clsInfo.addConstructor("integer|float|string x, integer|float|string y");

        clsInfo.addMember("float x");
        clsInfo.addMember("float y");

        clsInfo.addFunc("Drawing." + clsName + " _add(Drawing." + clsName + " c) const");
        clsInfo.addFunc("Drawing." + clsName + " _sub(Drawing." + clsName + " c) const");
        clsInfo.addFunc("Drawing." + clsName + " _unm(Drawing." + clsName + " c) const");
        clsInfo.addFunc("Drawing." + clsName + " _mul(Drawing." + clsName + " c) const");
        clsInfo.addFunc("Drawing." + clsName + " _div(Drawing." + clsName + " c) const");

        //clsInfo.addFunc("string toString() const");
        clsInfo.addFunc("string tostring() const");
        clsInfo.addFunc("string _tostring() const");

        return clsInfo;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("Coords"))
    {
        // const bool staticMethod = true ;
        // const bool classMethod  = false;

        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object ox, ssq::Object oy  /* float x, float y */  ) -> DrawingCoords*
                                {
                                    return new DrawingCoords{ marty_simplesquirrel::fromObjectConvertHelper<float>(ox, _SC("x")), marty_simplesquirrel::fromObjectConvertHelper<float>(oy, _SC("y"))};
                                }
                              , true // release
                              );

        cls.addVar(_SC("x"), &DrawingCoords::x);
        cls.addVar(_SC("y"), &DrawingCoords::y);

        // operators override
        cls.addFunc( _SC("_add") , &DrawingCoords::addImpl);
        cls.addFunc( _SC("_sub") , &DrawingCoords::subImpl);
        cls.addFunc( _SC("_unm") , &DrawingCoords::unmImpl);
        cls.addFunc( _SC("_mul") , &DrawingCoords::mulImpl);
        cls.addFunc( _SC("_div") , &DrawingCoords::divImpl);

        cls.addFunc( _SC("toString"), &DrawingCoords::toString);
        cls.addFunc( _SC("tostring"), &DrawingCoords::toString);
        cls.addFunc( _SC("_tostring"), &DrawingCoords::toString);

        return cls;
    }

}; // struct DrawingCoords



} // namespace simplesquirrel {
} // namespace marty_draw_context {
