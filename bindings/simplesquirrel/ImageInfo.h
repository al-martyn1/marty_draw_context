#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


ssq::Class exposeImageInfo(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("ImageInfo"))
{
    //const bool staticMethod = true ;
    //const bool classMethod  = false;

    auto cls = vm.addClass( className.c_str()
                          , []()
                            {
                                return new marty_draw_context::ImageListImageInfo();
                            }
                          , true // release
                          );

    cls.addVar(_SC("size")  , &marty_draw_context::ImageListImageInfo::imageSize);

    cls.addFunc( _SC("getMimeType")
               , [](marty_draw_context::ImageListImageInfo* self) -> ssq::sqstring
                 {
                     MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                     return marty_simplesquirrel::to_sqstring(self->mimeType);
                 }
               );

    cls.addFunc( _SC("getHasAlpha")
               , [](marty_draw_context::ImageListImageInfo* self) -> bool
                 {
                     MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                     return self->hasAlpha;
                 }
               );

    cls.addFunc( _SC("getHasMask")
               , [](marty_draw_context::ImageListImageInfo* self) -> bool
                 {
                     MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                     return self->hasMask;
                 }
               );

    return cls;
}



} // namespace simplesquirrel {
} // namespace marty_draw_context {

