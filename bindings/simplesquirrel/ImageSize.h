#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


ssq::Class exposeImageSize(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("ImageSize"))
{
    //const bool staticMethod = true ;
    //const bool classMethod  = false;

    auto cls = vm.addClass( className.c_str()
                          , [](int w, int h)
                            {
                                if (w<0)
                                    w = -w;
                                if (h<0)
                                    h = -h;
                                return new marty_draw_context::ImageSize{w,h};
                            }
                          , true // release
                          );

    cls.addVar(_SC("x")     , &marty_draw_context::ImageSize::width);
    cls.addVar(_SC("y")     , &marty_draw_context::ImageSize::height);
    cls.addVar(_SC("width") , &marty_draw_context::ImageSize::width);
    cls.addVar(_SC("height"), &marty_draw_context::ImageSize::height);

    return cls;
}



} // namespace simplesquirrel {
} // namespace marty_draw_context {

