#include "stdafx.h"
#include "r2_rendertarget.h"
 
void CRenderTarget::phase_fxaa()
{
    u32 Offset = 0;
    float _w = float(Device.dwWidth);
    float _h = float(Device.dwHeight);
    float du = ps_r1_pps_u, dv = ps_r1_pps_v;
 
    u_setrt(rt_Generic_0, 0, NULL, HW.pBaseZB);
    RCache.set_CullMode     ( CULL_NONE )   ;
    RCache.set_Stencil      ( FALSE     )   ;    
 
    FVF::V* pv = (FVF::V*)  RCache.Vertex.Lock(4, g_fxaa->vb_stride, Offset);
    pv->set(du - 0.5, dv + float(_h) - 0.5, 0, 0, 1);   pv++;
    pv->set(du - 0.5, dv - 0.5, 0, 0, 0);   pv++;
    pv->set(du + float(_w) - 0.5, dv + float(_h) - 0.5, 0, 1, 1);   pv++;
    pv->set(du + float(_w) - 0.5, dv -  0.5, 0, 1, 0);   pv++;
    RCache.Vertex.Unlock(4, g_fxaa->vb_stride);

   
    RCache.set_Element(s_fxaa->E[0]);
    RCache.set_Geometry(g_fxaa);
    RCache.Render(D3DPT_TRIANGLELIST, Offset, 0, 4, 0, 2);
 
    //HW.pDevice->CopyResource(rt_Generic_0->pTexture->surface_get(), rt_Generic->pTexture->surface_get());
       
}
