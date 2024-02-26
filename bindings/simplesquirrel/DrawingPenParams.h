#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct DrawingPenParams
{
    float         width  ;
    int           endcaps;
    int           join   ;

    DrawingPenParams() : width(1.0), endcaps(0), join(0) {}
    DrawingPenParams(float width_, int endcaps_, int join_) : width(width_), endcaps(endcaps_), join(join_) {}
    DrawingPenParams(const PenParams &pp) : width(floatToFloat(pp.width)), endcaps((int)pp.endcaps), join((int)pp.join) {}
    DrawingPenParams(const DrawingPenParams &) = default;
    DrawingPenParams(DrawingPenParams &&) = default;


    operator marty_draw_context::PenParams() const
    {
        marty_draw_context::PenParams pp;
        pp.width   = (marty_draw_context::DrawCoord::value_type)width  ;
        pp.endcaps = (LineEndcapStyle)endcaps;
        pp.join    = (LineJoinStyle)join   ;
        return pp;
    }

    static
    marty_simplesquirrel::ClassInfo getClassInfo(const std::string &clsName = "PenParams")
    {
        auto clsInfo = marty_simplesquirrel::ClassInfo(clsName);

        clsInfo.addConstructor("integer|float|string width, Drawing.LineEndcapStyle endcaps, Drawing.LineJoinStyle join");

        clsInfo.addMember("float width");
        clsInfo.addMember("Drawing.LineEndcapStyle endcaps");
        clsInfo.addMember("Drawing.LineJoinStyle join");

        return clsInfo;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("PenParams"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object w, ssq::Object ecaps, ssq::Object j )
                                {
                                    float         width_     = marty_simplesquirrel::fromObjectConvertHelper<float>(w, _SC("width"));
                                    int           endcaps_   = marty_simplesquirrel::fromObjectConvertHelper<int>(ecaps, _SC("endcaps"));
                                    int           join_      = marty_simplesquirrel::fromObjectConvertHelper<int>(j, _SC("join"));

                                    return new DrawingPenParams(width_, endcaps_, join_ );
                                }
                              , true // release
                              );


        // auto cls = vm.addClass( className.c_str(), []() { return new DrawingPenParams(); }, true /* release */ );

        cls.addVar(_SC("width")   , &DrawingPenParams::width   );
        cls.addVar(_SC("endcaps") , &DrawingPenParams::endcaps );
        cls.addVar(_SC("join")    , &DrawingPenParams::join    );

        return cls;
    }


}; // struct DrawingPenParams



} // namespace simplesquirrel {
} // namespace marty_draw_context {
