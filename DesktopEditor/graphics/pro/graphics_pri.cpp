﻿/*
 * (c) Copyright Ascensio System SIA 2010-2018
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at Lubanas st. 125a-25, Riga, Latvia,
 * EU, LV-1021.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#include "../../../graphics/ArrowHead.cpp"
#include "../../../graphics/Brush.cpp"
#include "../../../graphics/Clip.cpp"
#include "../../../graphics/Graphics.cpp"
#include "../../../graphics/GraphicsRenderer.cpp"
#include "../../../graphics/Image.cpp"

#include "../../../agg-2.4/src/agg_arc.cpp"
#include "../../../agg-2.4/src/agg_bezier_arc.cpp"
#include "../../../agg-2.4/src/agg_arrowhead.cpp"
#include "../../../agg-2.4/src/ctrl/agg_cbox_ctrl.cpp"
#include "../../../agg-2.4/src/agg_curves.cpp"
#include "../../../agg-2.4/src/agg_gsv_text.cpp"
#include "../../../agg-2.4/src/agg_image_filters.cpp"
#include "../../../agg-2.4/src/agg_line_aa_basics.cpp"
#include "../../../agg-2.4/src/agg_line_profile_aa.cpp"
#include "../../../agg-2.4/src/agg_rounded_rect.cpp"
#include "../../../agg-2.4/src/agg_sqrt_tables.cpp"
#include "../../../agg-2.4/src/agg_trans_affine.cpp"
#include "../../../agg-2.4/src/agg_bspline.cpp"
#include "../../../agg-2.4/src/agg_vcgen_bspline.cpp"
#include "../../../agg-2.4/src/agg_vcgen_contour.cpp"
#include "../../../agg-2.4/src/agg_vcgen_dash.cpp"
#include "../../../agg-2.4/src/agg_vcgen_markers_term.cpp"
#include "../../../agg-2.4/src/agg_vcgen_smooth_poly1.cpp"
#include "../../../agg-2.4/src/agg_vcgen_stroke.cpp"

/*
#include "../../../freetype-2.5.2/src/base/ftbbox.c"
#include "../../../freetype-2.5.2/src/base/ftgxval.c"
#include "../../../freetype-2.5.2/src/base/ftlcdfil.c"
#include "../../../freetype-2.5.2/src/base/ftmm.c"
#include "../../../freetype-2.5.2/src/base/ftotval.c"
#include "../../../freetype-2.5.2/src/base/ftpatent.c"
#include "../../../freetype-2.5.2/src/base/ftpfr.c"
#include "../../../freetype-2.5.2/src/base/ftsynth.c"
#include "../../../freetype-2.5.2/src/base/fttype1.c"
#include "../../../freetype-2.5.2/src/base/ftwinfnt.c"
#include "../../../freetype-2.5.2/src/base/ftxf86.c"
#include "../../../freetype-2.5.2/src/pcf/pcf.c"
#include "../../../freetype-2.5.2/src/pfr/pfr.c"
#include "../../../freetype-2.5.2/src/psaux/psaux.c"
#include "../../../freetype-2.5.2/src/pshinter/pshinter.c"
#include "../../../freetype-2.5.2/src/psnames/psmodule.c"
#include "../../../freetype-2.5.2/src/raster/raster.c"
#include "../../../freetype-2.5.2/src/sfnt/sfnt.c"
#include "../../../freetype-2.5.2/src/truetype/truetype.c"
#include "../../../freetype-2.5.2/src/type1/type1.c"
#include "../../../freetype-2.5.2/src/cid/type1cid.c"
#include "../../../freetype-2.5.2/src/type42/type42.c"
#include "../../../freetype-2.5.2/src/winfonts/winfnt.c"

#include "../../../freetype-2.5.2/src/autofit/autofit.c"
#include "../../../freetype-2.5.2/src/bdf/bdf.c"
#include "../../../freetype-2.5.2/src/cff/cff.c"
#include "../../../freetype-2.5.2/src/base/ftbase.c"
#include "../../../freetype-2.5.2/src/base/ftbitmap.c"
#include "../../../freetype-2.5.2/src/cache/ftcache.c"
#include "../../../freetype-2.5.2/src/base/ftfstype.c"
#include "../../../freetype-2.5.2/src/base/ftgasp.c"
#include "../../../freetype-2.5.2/src/base/ftglyph.c"
#include "../../../freetype-2.5.2/src/gzip/ftgzip.c"
#include "../../../freetype-2.5.2/src/base/ftinit.c"
#include "../../../freetype-2.5.2/src/lzw/ftlzw.c"
#include "../../../freetype-2.5.2/src/base/ftstroke.c"
#include "../../../freetype-2.5.2/src/base/ftsystem.c"
#include "../../../freetype-2.5.2/src/smooth/smooth.c"
*/

#include "../../../fontengine/ApplicationFonts.cpp"
#include "../../../fontengine/FontFile.cpp"
#include "../../../fontengine/FontManager.cpp"
#include "../../../fontengine/FontPath.cpp"
#include "../../../fontengine/GlyphString.cpp"

#include "../../../fontengine/fontconverter/StringExt.cpp"
#include "../../../fontengine/fontconverter/Hash.cpp"
#include "../../../fontengine/fontconverter/FontConverter.cpp"
#include "../../../fontengine/fontconverter/FontFileEncodings.cpp"
#include "../../../fontengine/fontconverter/FontFileTrueType.cpp"
#include "../../../fontengine/fontconverter/FontFileType1.cpp"
#include "../../../fontengine/fontconverter/FontFileType1C.cpp"

/*
#include "../../../cximage/jasper/bmp/bmp_cod.c"
#include "../../../cximage/jasper/bmp/bmp_dec.c"
#include "../../../cximage/jasper/bmp/bmp_enc.c"
#include "../../../cximage/jasper/jp2/jp2_cod.c"
#include "../../../cximage/jasper/jp2/jp2_dec.c"
#include "../../../cximage/jasper/jp2/jp2_enc.c"
#include "../../../cximage/jasper/jpc/jpc_bs.c"
#include "../../../cximage/jasper/jpc/jpc_cs.c"
#include "../../../cximage/jasper/jpc/jpc_dec.c"
#include "../../../cximage/jasper/jpc/jpc_enc.c"
#include "../../../cximage/jasper/jpc/jpc_math.c"
#include "../../../cximage/jasper/jpc/jpc_mct.c"
#include "../../../cximage/jasper/jpc/jpc_mqcod.c"
#include "../../../cximage/jasper/jpc/jpc_mqdec.c"
#include "../../../cximage/jasper/jpc/jpc_mqenc.c"
#include "../../../cximage/jasper/jpc/jpc_qmfb.c"
#include "../../../cximage/jasper/jpc/jpc_t1cod.c"
#include "../../../cximage/jasper/jpc/jpc_t1dec.c"
#include "../../../cximage/jasper/jpc/jpc_t1enc.c"
#include "../../../cximage/jasper/jpc/jpc_t2cod.c"
#include "../../../cximage/jasper/jpc/jpc_t2dec.c"
#include "../../../cximage/jasper/jpc/jpc_t2enc.c"
#include "../../../cximage/jasper/jpc/jpc_tagtree.c"
#include "../../../cximage/jasper/jpc/jpc_tsfb.c"
#include "../../../cximage/jasper/jpc/jpc_util.c"
#include "../../../cximage/jasper/jpg/jpg_dummy.c"
#include "../../../cximage/jasper/jpg/jpg_val.c"
#include "../../../cximage/jasper/mif/mif_cod.c"
#include "../../../cximage/jasper/pgx/pgx_cod.c"
#include "../../../cximage/jasper/pgx/pgx_dec.c"
#include "../../../cximage/jasper/pgx/pgx_enc.c"
#include "../../../cximage/jasper/pnm/pnm_cod.c"
#include "../../../cximage/jasper/pnm/pnm_dec.c"
#include "../../../cximage/jasper/pnm/pnm_enc.c"
#include "../../../cximage/jasper/ras/ras_cod.c"
#include "../../../cximage/jasper/ras/ras_dec.c"
#include "../../../cximage/jasper/ras/ras_enc.c"

#include "../../../cximage/jbig/jbig.c"
#include "../../../cximage/jbig/jbig_tab.c"

#include "../../../cximage/jpeg/wrtarga.c"
#include "../../../cximage/jpeg/wrrle.c"
#include "../../../cximage/jpeg/wrppm.c"
#include "../../../cximage/jpeg/wrjpgcom.c"
#include "../../../cximage/jpeg/wrgif.c"
#include "../../../cximage/jpeg/wrbmp.c"
#include "../../../cximage/jpeg/transupp.c"
#include "../../../cximage/jpeg/rdtarga.c"
#include "../../../cximage/jpeg/rdswitch.c"
#include "../../../cximage/jpeg/rdrle.c"
#include "../../../cximage/jpeg/rdppm.c"
#include "../../../cximage/jpeg/rdjpgcom.c"
#include "../../../cximage/jpeg/rdgif.c"
#include "../../../cximage/jpeg/rdcolmap.c"
#include "../../../cximage/jpeg/rdbmp.c"
#include "../../../cximage/jpeg/jutils.c"
#include "../../../cximage/jpeg/jpegtran.c"
#include "../../../cximage/jpeg/jquant1.c"
#include "../../../cximage/jpeg/jquant2.c"
#include "../../../cximage/jpeg/jdpostct.c"
#include "../../../cximage/jpeg/jdsample.c"
#include "../../../cximage/jpeg/jdtrans.c"
#include "../../../cximage/jpeg/jerror.c"
#include "../../../cximage/jpeg/jfdctflt.c"
#include "../../../cximage/jpeg/jfdctfst.c"
#include "../../../cximage/jpeg/jfdctint.c"
#include "../../../cximage/jpeg/jidctflt.c"
#include "../../../cximage/jpeg/jidctfst.c"
#include "../../../cximage/jpeg/jidctint.c"
//#include "../../../cximage/jpeg/jmemansi.c"
#include "../../../cximage/jpeg/jmemmgr.c"
//#include "../../../cximage/jpeg/jmemname.c"
#include "../../../cximage/jpeg/jmemnobs.c"
#include "../../../cximage/jpeg/jaricom.c"
#include "../../../cximage/jpeg/jcapimin.c"
#include "../../../cximage/jpeg/jcapistd.c"
#include "../../../cximage/jpeg/jcarith.c"
#include "../../../cximage/jpeg/jccoefct.c"
#include "../../../cximage/jpeg/jccolor.c"
#include "../../../cximage/jpeg/jcdctmgr.c"
#include "../../../cximage/jpeg/jchuff.c"
#include "../../../cximage/jpeg/jcinit.c"
#include "../../../cximage/jpeg/jcmainct.c"
#include "../../../cximage/jpeg/jcmarker.c"
#include "../../../cximage/jpeg/jcmaster.c"
#include "../../../cximage/jpeg/jcomapi.c"
#include "../../../cximage/jpeg/jcparam.c"
#include "../../../cximage/jpeg/jcprepct.c"
#include "../../../cximage/jpeg/jcsample.c"
#include "../../../cximage/jpeg/jctrans.c"
#include "../../../cximage/jpeg/jdapimin.c"
#include "../../../cximage/jpeg/jdapistd.c"
#include "../../../cximage/jpeg/jdarith.c"
#include "../../../cximage/jpeg/jdatadst.c"
#include "../../../cximage/jpeg/jdatasrc.c"
#include "../../../cximage/jpeg/jdcoefct.c"
#include "../../../cximage/jpeg/jdcolor.c"
#include "../../../cximage/jpeg/jddctmgr.c"
#include "../../../cximage/jpeg/jdhuff.c"
#include "../../../cximage/jpeg/jdinput.c"
#include "../../../cximage/jpeg/jdmainct.c"
#include "../../../cximage/jpeg/jdmarker.c"
#include "../../../cximage/jpeg/jdmaster.c"
#include "../../../cximage/jpeg/jdmerge.c"
#include "../../../cximage/jpeg/cdjpeg.c"
#include "../../../cximage/jpeg/cjpeg.c"
#include "../../../cximage/jpeg/ckconfig.c"
#include "../../../cximage/jpeg/djpeg.c"
#include "../../../cximage/jpeg/example.c"

#include "../../../cximage/libpsd/adjustment.c"
#include "../../../cximage/libpsd/bevel_emboss.c"
#include "../../../cximage/libpsd/bitmap.c"
#include "../../../cximage/libpsd/blend.c"
#include "../../../cximage/libpsd/boundary.c"
#include "../../../cximage/libpsd/brightness_contrast.c"
#include "../../../cximage/libpsd/channel_image.c"
#include "../../../cximage/libpsd/channel_mixer.c"
#include "../../../cximage/libpsd/color_balance.c"
#include "../../../cximage/libpsd/color_mode.c"
#include "../../../cximage/libpsd/color_overlay.c"
#include "../../../cximage/libpsd/color.c"
#include "../../../cximage/libpsd/curves.c"
#include "../../../cximage/libpsd/descriptor.c"
#include "../../../cximage/libpsd/drop_shadow.c"
#include "../../../cximage/libpsd/effects.c"
#include "../../../cximage/libpsd/file_header.c"
#include "../../../cximage/libpsd/fixed.c"
#include "../../../cximage/libpsd/gaussian_blur.c"
#include "../../../cximage/libpsd/gradient_blend.c"
#include "../../../cximage/libpsd/gradient_fill.c"
#include "../../../cximage/libpsd/gradient_map.c"
#include "../../../cximage/libpsd/gradient_overlay.c"
#include "../../../cximage/libpsd/hue_saturation.c"
#include "../../../cximage/libpsd/image_data.c"
#include "../../../cximage/libpsd/image_resource.c"
#include "../../../cximage/libpsd/inner_glow.c"
#include "../../../cximage/libpsd/inner_shadow.c"
#include "../../../cximage/libpsd/invert.c"
#include "../../../cximage/libpsd/layer_mask.c"
#include "../../../cximage/libpsd/levels.c"
#include "../../../cximage/libpsd/outer_glow.c"
#include "../../../cximage/libpsd/path.c"
#include "../../../cximage/libpsd/pattern_fill.c"
#include "../../../cximage/libpsd/pattern_overlay.c"
#include "../../../cximage/libpsd/pattern.c"
#include "../../../cximage/libpsd/photo_filter.c"
#include "../../../cximage/libpsd/posterize.c"
#include "../../../cximage/libpsd/psd_system.c"
#include "../../../cximage/libpsd/psd_zip.c"
#include "../../../cximage/libpsd/psd.c"
#include "../../../cximage/libpsd/rect.c"
#include "../../../cximage/libpsd/satin.c"
#include "../../../cximage/libpsd/selective_color.c"
#include "../../../cximage/libpsd/solid_color.c"
#include "../../../cximage/libpsd/stream.c"
#include "../../../cximage/libpsd/stroke.c"
#include "../../../cximage/libpsd/threshold.c"
#include "../../../cximage/libpsd/thumbnail.c"
#include "../../../cximage/libpsd/type_tool.c"

#include "../../../cximage/mng/libmng_callback_xs.c"
#include "../../../cximage/mng/libmng_chunk_descr.c"
#include "../../../cximage/mng/libmng_chunk_io.c"
#include "../../../cximage/mng/libmng_chunk_prc.c"
#include "../../../cximage/mng/libmng_chunk_xs.c"
#include "../../../cximage/mng/libmng_cms.c"
#include "../../../cximage/mng/libmng_display.c"
#include "../../../cximage/mng/libmng_dither.c"
#include "../../../cximage/mng/libmng_error.c"
#include "../../../cximage/mng/libmng_filter.c"
#include "../../../cximage/mng/libmng_hlapi.c"
#include "../../../cximage/mng/libmng_jpeg.c"
#include "../../../cximage/mng/libmng_object_prc.c"
#include "../../../cximage/mng/libmng_pixels.c"
#include "../../../cximage/mng/libmng_prop_xs.c"
#include "../../../cximage/mng/libmng_read.c"
#include "../../../cximage/mng/libmng_trace.c"
#include "../../../cximage/mng/libmng_write.c"
#include "../../../cximage/mng/libmng_zlib.c"

#include "../../../cximage/png/png.c"
#include "../../../cximage/png/pngerror.c"
#include "../../../cximage/png/pngget.c"
#include "../../../cximage/png/pngmem.c"
#include "../../../cximage/png/pngpread.c"
#include "../../../cximage/png/pngread.c"
#include "../../../cximage/png/pngrio.c"
#include "../../../cximage/png/pngrtran.c"
#include "../../../cximage/png/pngrutil.c"
#include "../../../cximage/png/pngset.c"
#include "../../../cximage/png/pngtrans.c"
#include "../../../cximage/png/pngwio.c"
#include "../../../cximage/png/pngwrite.c"
#include "../../../cximage/png/pngwtran.c"
#include "../../../cximage/png/pngwutil.c"

#include "../../../cximage/raw/libdcr.c"

#include "../../../cximage/tiff/tif_stream.cxx"
#include "../../../cximage/tiff/tif_aux.c"
#include "../../../cximage/tiff/tif_close.c"
#include "../../../cximage/tiff/tif_codec.c"
#include "../../../cximage/tiff/tif_color.c"
#include "../../../cximage/tiff/tif_compress.c"
#include "../../../cximage/tiff/tif_dir.c"
#include "../../../cximage/tiff/tif_dirinfo.c"
#include "../../../cximage/tiff/tif_dirread.c"
#include "../../../cximage/tiff/tif_dirwrite.c"
#include "../../../cximage/tiff/tif_dumpmode.c"
#include "../../../cximage/tiff/tif_error.c"
#include "../../../cximage/tiff/tif_extension.c"
#include "../../../cximage/tiff/tif_fax3.c"
#include "../../../cximage/tiff/tif_fax3sm.c"
#include "../../../cximage/tiff/tif_flush.c"
#include "../../../cximage/tiff/tif_getimage.c"
#include "../../../cximage/tiff/tif_jbig.c"
#include "../../../cximage/tiff/tif_jpeg.c"
#include "../../../cximage/tiff/tif_luv.c"
#include "../../../cximage/tiff/tif_lzw.c"
#include "../../../cximage/tiff/tif_next.c"
#include "../../../cximage/tiff/tif_ojpeg.c"
#include "../../../cximage/tiff/tif_open.c"
#include "../../../cximage/tiff/tif_packbits.c"
#include "../../../cximage/tiff/tif_pixarlog.c"
#include "../../../cximage/tiff/tif_predict.c"
#include "../../../cximage/tiff/tif_print.c"
#include "../../../cximage/tiff/tif_read.c"
#include "../../../cximage/tiff/tif_strip.c"
#include "../../../cximage/tiff/tif_swab.c"
#include "../../../cximage/tiff/tif_thunder.c"
#include "../../../cximage/tiff/tif_tile.c"
#include "../../../cximage/tiff/tif_unix.c"
#include "../../../cximage/tiff/tif_version.c"
#include "../../../cximage/tiff/tif_warning.c"
#include "../../../cximage/tiff/tif_write.c"
#include "../../../cximage/tiff/tif_zip.c"

#include "../../../cximage/zlib/crc32.c
#include "../../../cximage/zlib/adler32.c"
#include "../../../cximage/zlib/deflate.c"
#include "../../../cximage/zlib/inffast.c"
#include "../../../cximage/zlib/inflate.c"
#include "../../../cximage/zlib/inftrees.c"
#include "../../../cximage/zlib/trees.c"
#include "../../../cximage/zlib/zutil.c"
#include "../../../cximage/zlib/uncompr.c"
#include "../../../cximage/zlib/compress.c"

#include "../../../cximage/CxImage/tif_xfile.cpp"
#include "../../../cximage/CxImage/ximabmp.cpp"
#include "../../../cximage/CxImage/ximadsp.cpp"
#include "../../../cximage/CxImage/ximaenc.cpp"
#include "../../../cximage/CxImage/ximaexif.cpp"
#include "../../../cximage/CxImage/ximage.cpp"
#include "../../../cximage/CxImage/ximagif.cpp"
#include "../../../cximage/CxImage/ximahist.cpp"
#include "../../../cximage/CxImage/ximaico.cpp"
#include "../../../cximage/CxImage/ximainfo.cpp"
#include "../../../cximage/CxImage/ximaint.cpp"
#include "../../../cximage/CxImage/ximajas.cpp"
#include "../../../cximage/CxImage/ximajbg.cpp"
#include "../../../cximage/CxImage/ximajpg.cpp"
#include "../../../cximage/CxImage/ximalpha.cpp"
#include "../../../cximage/CxImage/ximalyr.cpp"
#include "../../../cximage/CxImage/ximamng.cpp"
#include "../../../cximage/CxImage/ximapal.cpp"
#include "../../../cximage/CxImage/ximapcx.cpp"
#include "../../../cximage/CxImage/ximapng.cpp"
#include "../../../cximage/CxImage/ximapsd.cpp"
#include "../../../cximage/CxImage/ximaraw.cpp"
#include "../../../cximage/CxImage/ximasel.cpp"
#include "../../../cximage/CxImage/ximaska.cpp"
#include "../../../cximage/CxImage/ximatga.cpp"
#include "../../../cximage/CxImage/ximath.cpp"
#include "../../../cximage/CxImage/ximatif.cpp"
#include "../../../cximage/CxImage/ximatran.cpp"
#include "../../../cximage/CxImage/ximawbmp.cpp"
#include "../../../cximage/CxImage/ximawmf.cpp"
#include "../../../cximage/CxImage/ximawnd.cpp"
#include "../../../cximage/CxImage/xmemfile.cpp"
*/

#include "../../../raster/Jp2/J2kFile.cpp"
#include "../../../raster/Jp2/Reader.cpp"
#include "../../../raster/Metafile/Common/MetaFileTypes.cpp"
#include "../../../raster/Metafile/Common/MetaFileUtils.cpp"
#include "../../../raster/Metafile/Emf/EmfClip.cpp"
#include "../../../raster/Metafile/Emf/EmfObjects.cpp"
#include "../../../raster/Metafile/Emf/EmfPath.cpp"
#include "../../../raster/Metafile/Emf/EmfPlayer.cpp"
#include "../../../raster/Metafile/Emf/EmfFile.cpp"
#include "../../../raster/Metafile/Wmf/WmfClip.cpp"
#include "../../../raster/Metafile/Wmf/WmfObjects.cpp"
#include "../../../raster/Metafile/Wmf/WmfPlayer.cpp"
#include "../../../raster/Metafile/MetaFile.cpp"
#include "../../../raster/JBig2/source/JBig2File.cpp"

/*
#include "../../../raster/JBig2/source/Encoder/jbig2arith.cpp"
#include "../../../raster/JBig2/source/Encoder/jbig2enc.cpp"
#include "../../../raster/JBig2/source/Encoder/jbig2sym.cpp"
#include "../../../raster/JBig2/source/LeptonLib/adaptmap.cpp"
#include "../../../raster/JBig2/source/LeptonLib/affine.cpp"
#include "../../../raster/JBig2/source/LeptonLib/affinecompose.cpp"
#include "../../../raster/JBig2/source/LeptonLib/arithlow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/arrayaccess.cpp"
#include "../../../raster/JBig2/source/LeptonLib/bardecode.cpp"
#include "../../../raster/JBig2/source/LeptonLib/baseline.cpp"
#include "../../../raster/JBig2/source/LeptonLib/bbuffer.cpp"
#include "../../../raster/JBig2/source/LeptonLib/bilinear.cpp"
#include "../../../raster/JBig2/source/LeptonLib/binarize.cpp"
#include "../../../raster/JBig2/source/LeptonLib/binexpand.cpp"
#include "../../../raster/JBig2/source/LeptonLib/binexpandlow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/binreduce.cpp"
#include "../../../raster/JBig2/source/LeptonLib/binreducelow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/bmf.cpp"
#include "../../../raster/JBig2/source/LeptonLib/bmpio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/bmpiostub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/boxbasic.cpp"
#include "../../../raster/JBig2/source/LeptonLib/boxfunc1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/boxfunc2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/boxfunc3.cpp"
#include "../../../raster/JBig2/source/LeptonLib/ccbord.cpp"
#include "../../../raster/JBig2/source/LeptonLib/ccthin.cpp"
#include "../../../raster/JBig2/source/LeptonLib/classapp.cpp"
#include "../../../raster/JBig2/source/LeptonLib/colorcontent.cpp"
#include "../../../raster/JBig2/source/LeptonLib/colormap.cpp"
#include "../../../raster/JBig2/source/LeptonLib/colormorph.cpp"
#include "../../../raster/JBig2/source/LeptonLib/colorquant1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/colorquant2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/colorseg.cpp"
#include "../../../raster/JBig2/source/LeptonLib/compare.cpp"
#include "../../../raster/JBig2/source/LeptonLib/conncomp.cpp"
#include "../../../raster/JBig2/source/LeptonLib/convertfiles.cpp"
#include "../../../raster/JBig2/source/LeptonLib/convolve.cpp"
#include "../../../raster/JBig2/source/LeptonLib/convolvelow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/correlscore.cpp"
#include "../../../raster/JBig2/source/LeptonLib/dewarp.cpp"
#include "../../../raster/JBig2/source/LeptonLib/dwacomb.2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/dwacomblow.2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/edge.cpp"
#include "../../../raster/JBig2/source/LeptonLib/enhance.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fhmtauto.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fhmtgen.1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fhmtgenlow.1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/finditalic.cpp"
#include "../../../raster/JBig2/source/LeptonLib/flipdetect.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fliphmtgen.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fmorphauto.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fmorphgen.1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fmorphgenlow.1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fpix1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/fpix2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/freetype.cpp"
#include "../../../raster/JBig2/source/LeptonLib/gifio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/gifiostub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/gplot.cpp"
#include "../../../raster/JBig2/source/LeptonLib/graphics1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/graymorph.cpp"
#include "../../../raster/JBig2/source/LeptonLib/graymorphlow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/grayquant.cpp"
#include "../../../raster/JBig2/source/LeptonLib/grayquantlow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/heap.cpp"
#include "../../../raster/JBig2/source/LeptonLib/jbclass.cpp"
#include "../../../raster/JBig2/source/LeptonLib/jpegio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/jpegiostub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/kernel.cpp"
#include "../../../raster/JBig2/source/LeptonLib/list.cpp"
#include "../../../raster/JBig2/source/LeptonLib/maze.cpp"
#include "../../../raster/JBig2/source/LeptonLib/morph.cpp"
#include "../../../raster/JBig2/source/LeptonLib/morphapp.cpp"
#include "../../../raster/JBig2/source/LeptonLib/morphdwa.cpp"
#include "../../../raster/JBig2/source/LeptonLib/morphseq.cpp"
#include "../../../raster/JBig2/source/LeptonLib/numabasic.cpp"
#include "../../../raster/JBig2/source/LeptonLib/numafunc1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/numafunc2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pageseg.cpp"
#include "../../../raster/JBig2/source/LeptonLib/paintcmap.cpp"
#include "../../../raster/JBig2/source/LeptonLib/parseprotos.cpp"
#include "../../../raster/JBig2/source/LeptonLib/partition.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pix1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pix2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pix3.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pix4.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pix5.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixabasic.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixacc.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixafunc1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixafunc2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixalloc.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixarith.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixcomp.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixconv.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pixtiling.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pngio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pngiostub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pnmio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/pnmiostub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/projective.cpp"
#include "../../../raster/JBig2/source/LeptonLib/psio1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/psio1stub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/psio2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/psio2stub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/ptabasic.cpp"
#include "../../../raster/JBig2/source/LeptonLib/ptafunc1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/ptra.cpp"
#include "../../../raster/JBig2/source/LeptonLib/queue.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rank.cpp"
#include "../../../raster/JBig2/source/LeptonLib/readbarcode.cpp"
#include "../../../raster/JBig2/source/LeptonLib/readfile.cpp"
#include "../../../raster/JBig2/source/LeptonLib/regutils.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rop.cpp"
#include "../../../raster/JBig2/source/LeptonLib/ropiplow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/roplow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rotate.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rotateam.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rotateamlow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rotateorth.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rotateorthlow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/rotateshear.cpp"
#include "../../../raster/JBig2/source/LeptonLib/runlength.cpp"
#include "../../../raster/JBig2/source/LeptonLib/sarray.cpp"
#include "../../../raster/JBig2/source/LeptonLib/scale.cpp"
#include "../../../raster/JBig2/source/LeptonLib/scalelow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/seedfill.cpp"
#include "../../../raster/JBig2/source/LeptonLib/seedfilllow.cpp"
#include "../../../raster/JBig2/source/LeptonLib/sel1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/sel2.cpp"
#include "../../../raster/JBig2/source/LeptonLib/selgen.cpp"
#include "../../../raster/JBig2/source/LeptonLib/shear.cpp"
#include "../../../raster/JBig2/source/LeptonLib/skew.cpp"
#include "../../../raster/JBig2/source/LeptonLib/spixio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/stack.cpp"
#include "../../../raster/JBig2/source/LeptonLib/sudoku.cpp"
#include "../../../raster/JBig2/source/LeptonLib/textops.cpp"
#include "../../../raster/JBig2/source/LeptonLib/tiffio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/tiffiostub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/utils.cpp"
#include "../../../raster/JBig2/source/LeptonLib/viewfiles.cpp"
#include "../../../raster/JBig2/source/LeptonLib/warper.cpp"
#include "../../../raster/JBig2/source/LeptonLib/watershed.cpp"
#include "../../../raster/JBig2/source/LeptonLib/webpio.cpp"
#include "../../../raster/JBig2/source/LeptonLib/webpiostub.cpp"
#include "../../../raster/JBig2/source/LeptonLib/writefile.cpp"
#include "../../../raster/JBig2/source/LeptonLib/zlibmem.cpp"
#include "../../../raster/JBig2/source/LeptonLib/zlibmemstub.cpp"
#include "../../../cximage/libpsd/test.c"
#include "../../../raster/JBig2/source/LeptonLib/blend1.cpp"
#include "../../../raster/JBig2/source/LeptonLib/blend1.cpp"
*/

#include "../../../raster/Metafile/StarView/SvmClip.cpp"
#include "../../../raster/Metafile/StarView/SvmFile.cpp"
#include "../../../raster/Metafile/StarView/SvmObjects.cpp"
#include "../../../raster/Metafile/StarView/SvmPlayer.cpp"
