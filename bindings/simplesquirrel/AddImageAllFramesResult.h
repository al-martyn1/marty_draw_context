#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct AddImageAllFramesResult
{
    int                firstImageId    = -1;
    int                numberOfFrames  = 0;

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("AddImageAllFramesResult"))
    {

        auto cls = vm.addClass( className.c_str()
                              , []()
                                {
                                    return new AddImageAllFramesResult();
                                }
                              , true // release
                              );


        cls.addVar(_SC("firstImageId")   , &AddImageAllFramesResult::firstImageId);
        cls.addVar(_SC("numberOfFrames") , &AddImageAllFramesResult::numberOfFrames);

        return cls;
    }

}; // struct AddImageAllFramesResult


} // namespace simplesquirrel {
} // namespace marty_draw_context {
