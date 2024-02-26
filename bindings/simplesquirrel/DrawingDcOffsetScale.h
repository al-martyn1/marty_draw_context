#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct DrawingDcOffsetScale
{
    DrawingCoords    offset  ;
    DrawingCoords    scale   ;
    float            penScale;

    DrawingDcOffsetScale() = default;
    DrawingDcOffsetScale(const DrawingDcOffsetScale &) = default;
    DrawingDcOffsetScale(const DcOffsetScale &os)
    : offset  (os.offset  )
    , scale   (os.scale   )
    , penScale(floatToFloat(os.penScale))
    {}

    operator marty_draw_context::DcOffsetScale() const
    {
        DcOffsetScale os;

        os.offset   = offset  ;
        os.scale    = scale   ;
        os.penScale = penScale;

        return os;
    }

}; // struct DrawingDcOffsetScale



} // namespace simplesquirrel {
} // namespace marty_draw_context {
