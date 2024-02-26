#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct DrawingDcResourcesState
{
    int             nPens      = 0;
    int             penId      = 0;
    int             nBrushes   = 0;
    int             brushId    = 0;
    int             nFonts     = 0;
    int             fontId     = 0;
    DrawingColor    textColor;
    DrawingColor    bkColor  ;

    DrawingDcResourcesState() = default;
    DrawingDcResourcesState(const DrawingDcResourcesState &) = default;
    DrawingDcResourcesState(const DcResourcesState &rcState)
    : nPens    (rcState.nPens    )
    , penId    (rcState.penId    )
    , nBrushes (rcState.nBrushes )
    , brushId  (rcState.brushId  )
    , nFonts   (rcState.nFonts   )
    , fontId   (rcState.fontId   )
    , textColor(rcState.textColor)
    , bkColor  (rcState.bkColor  )
    {}

    operator marty_draw_context::DcResourcesState() const
    {
        DcResourcesState rcState;

        rcState.nPens     = nPens    ;
        rcState.penId     = penId    ;
        rcState.nBrushes  = nBrushes ;
        rcState.brushId   = brushId  ;
        rcState.nFonts    = nFonts   ;
        rcState.fontId    = fontId   ;
        rcState.textColor = textColor;
        rcState.bkColor   = bkColor  ;

        return rcState;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("DcResourcesState"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []() { return new DcResourcesState(); }
                              , true /* release */
                              );
        return cls;
    }

}; // struct DrawingDcResourcesState



} // namespace simplesquirrel {
} // namespace marty_draw_context {
