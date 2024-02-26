#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct DrawingGradientParams
{
    DrawingColor     colorBegin;
    DrawingColor     colorMid  ;
    DrawingColor     colorEnd  ;

    float         midPoint  = (DrawCoord::value_type)0.5;

    operator marty_draw_context::GradientParams() const
    {
        marty_draw_context::GradientParams gpRes;
        gpRes.colorBegin = colorBegin;
        gpRes.colorMid   = colorMid  ;
        gpRes.colorEnd   = colorEnd  ;
        gpRes.midPoint   = (marty_draw_context::DrawCoord::value_type)midPoint;

        return gpRes;
    }
    
    static
    marty_simplesquirrel::ClassInfo getClassInfo(const std::string &clsName = "GradientParams")
    {
        auto clsInfo = marty_simplesquirrel::ClassInfo(clsName);

        clsInfo.addConstructor("Drawing.Color colorBegin, Drawing.Color colorMid, Drawing.Color colorEnd, integer|float|string midPointPos");

        clsInfo.addMember("Drawing.Color colorBegin");
        clsInfo.addMember("Drawing.Color colorMid");
        clsInfo.addMember("Drawing.Color colorEnd");
        clsInfo.addMember("float midPoint");

        return clsInfo;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("GradientParams"))
    {
        auto cls = vm.addClass( className.c_str()
                              , [](DrawingColor b, DrawingColor m, DrawingColor e, ssq::Object mp)
                                {
                                    float mp_         = marty_simplesquirrel::fromObjectConvertHelper<float>(mp, _SC("midPont"));
                                    return new DrawingGradientParams{b, m, e, mp_};
                                }
                              , true /* release */
                              );

        cls.addVar(_SC("colorBegin") , &DrawingGradientParams::colorBegin );
        cls.addVar(_SC("colorMid")   , &DrawingGradientParams::colorMid   );
        cls.addVar(_SC("colorEnd")   , &DrawingGradientParams::colorEnd   );
        cls.addVar(_SC("midPoint")   , &DrawingGradientParams::midPoint   );

        return cls;
    }

}; // struct DrawingGradientParams



} // namespace simplesquirrel {
} // namespace marty_draw_context {
