#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct AddImageBandResult
{
    int                imageId = -1;
    bool               verticalBand = false;
    ImageSize          frameSize{0,0};


    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("AddImageBandResult"))
    {

        auto cls = vm.addClass( className.c_str()
                              , []()
                                {
                                    return new AddImageBandResult();
                                }
                              , true // release
                              );


        cls.addVar(_SC("imageId")      , &AddImageBandResult::imageId);
        cls.addVar(_SC("verticalBand") , &AddImageBandResult::verticalBand);
        cls.addVar(_SC("frameSize")    , &AddImageBandResult::frameSize);

        return cls;
    }

}; // struct AddImageBandResult


} // namespace simplesquirrel {
} // namespace marty_draw_context {
