//***************************************************************************************
// d3dUtil.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "Vect.h"
#include "Enum.h"

#ifndef D3DUTIL_H
#define D3DUTIL_H


// Convenience macro for releasing COM objects.
#define ReleaseAndDeleteCOMobject(x) { if(x){ x->Release(); x = 0; } }

// Hack to pass a Vect as a array of floats (only needed for ClearRenderTargetView)
#define VasA(v) { &v[x] }

namespace Colors
{
	// Standard colors (Red/Green/Blue/Alpha)
	const Vect AliceBlue = { 0.941176534f, 0.972549081f, 1.000000000f, 1.000000000f };
	const Vect AntiqueWhite = { 0.980392218f, 0.921568692f, 0.843137324f, 1.000000000f };
	const Vect Aqua = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vect Aquamarine = { 0.498039246f, 1.000000000f, 0.831372619f, 1.000000000f };
	const Vect Azure = { 0.941176534f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vect Beige = { 0.960784376f, 0.960784376f, 0.862745166f, 1.000000000f };
	const Vect Bisque = { 1.000000000f, 0.894117713f, 0.768627524f, 1.000000000f };
	const Vect Black = { 0.000000000f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vect BlanchedAlmond = { 1.000000000f, 0.921568692f, 0.803921640f, 1.000000000f };
	const Vect Blue = { 0.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	const Vect BlueViolet = { 0.541176498f, 0.168627456f, 0.886274576f, 1.000000000f };
	const Vect Brown = { 0.647058845f, 0.164705887f, 0.164705887f, 1.000000000f };
	const Vect BurlyWood = { 0.870588303f, 0.721568644f, 0.529411793f, 1.000000000f };
	const Vect CadetBlue = { 0.372549027f, 0.619607866f, 0.627451003f, 1.000000000f };
	const Vect Chartreuse = { 0.498039246f, 1.000000000f, 0.000000000f, 1.000000000f };
	const Vect Chocolate = { 0.823529482f, 0.411764741f, 0.117647067f, 1.000000000f };
	const Vect Coral = { 1.000000000f, 0.498039246f, 0.313725501f, 1.000000000f };
	const Vect CornflowerBlue = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };
	const Vect Cornsilk = { 1.000000000f, 0.972549081f, 0.862745166f, 1.000000000f };
	const Vect Crimson = { 0.862745166f, 0.078431375f, 0.235294133f, 1.000000000f };
	const Vect Cyan = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vect DarkBlue = { 0.000000000f, 0.000000000f, 0.545098066f, 1.000000000f };
	const Vect DarkCyan = { 0.000000000f, 0.545098066f, 0.545098066f, 1.000000000f };
	const Vect DarkGoldenrod = { 0.721568644f, 0.525490224f, 0.043137256f, 1.000000000f };
	const Vect DarkGray = { 0.662745118f, 0.662745118f, 0.662745118f, 1.000000000f };
	const Vect DarkGreen = { 0.000000000f, 0.392156899f, 0.000000000f, 1.000000000f };
	const Vect DarkKhaki = { 0.741176486f, 0.717647076f, 0.419607878f, 1.000000000f };
	const Vect DarkMagenta = { 0.545098066f, 0.000000000f, 0.545098066f, 1.000000000f };
	const Vect DarkOliveGreen = { 0.333333343f, 0.419607878f, 0.184313729f, 1.000000000f };
	const Vect DarkOrange = { 1.000000000f, 0.549019635f, 0.000000000f, 1.000000000f };
	const Vect DarkOrchid = { 0.600000024f, 0.196078449f, 0.800000072f, 1.000000000f };
	const Vect DarkRed = { 0.545098066f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vect DarkSalmon = { 0.913725555f, 0.588235319f, 0.478431404f, 1.000000000f };
	const Vect DarkSeaGreen = { 0.560784340f, 0.737254918f, 0.545098066f, 1.000000000f };
	const Vect DarkSlateBlue = { 0.282352954f, 0.239215702f, 0.545098066f, 1.000000000f };
	const Vect DarkSlateGray = { 0.184313729f, 0.309803933f, 0.309803933f, 1.000000000f };
	const Vect DarkTurquoise = { 0.000000000f, 0.807843208f, 0.819607913f, 1.000000000f };
	const Vect DarkViolet = { 0.580392182f, 0.000000000f, 0.827451050f, 1.000000000f };
	const Vect DeepPink = { 1.000000000f, 0.078431375f, 0.576470613f, 1.000000000f };
	const Vect DeepSkyBlue = { 0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f };
	const Vect DimGray = { 0.411764741f, 0.411764741f, 0.411764741f, 1.000000000f };
	const Vect DodgerBlue = { 0.117647067f, 0.564705908f, 1.000000000f, 1.000000000f };
	const Vect Firebrick = { 0.698039234f, 0.133333340f, 0.133333340f, 1.000000000f };
	const Vect FloralWhite = { 1.000000000f, 0.980392218f, 0.941176534f, 1.000000000f };
	const Vect ForestGreen = { 0.133333340f, 0.545098066f, 0.133333340f, 1.000000000f };
	const Vect Fuchsia = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	const Vect Gainsboro = { 0.862745166f, 0.862745166f, 0.862745166f, 1.000000000f };
	const Vect GhostWhite = { 0.972549081f, 0.972549081f, 1.000000000f, 1.000000000f };
	const Vect Gold = { 1.000000000f, 0.843137324f, 0.000000000f, 1.000000000f };
	const Vect Goldenrod = { 0.854902029f, 0.647058845f, 0.125490203f, 1.000000000f };
	const Vect Gray = { 0.501960814f, 0.501960814f, 0.501960814f, 1.000000000f };
	const Vect Green = { 0.000000000f, 0.501960814f, 0.000000000f, 1.000000000f };
	const Vect GreenYellow = { 0.678431392f, 1.000000000f, 0.184313729f, 1.000000000f };
	const Vect Honeydew = { 0.941176534f, 1.000000000f, 0.941176534f, 1.000000000f };
	const Vect HotPink = { 1.000000000f, 0.411764741f, 0.705882370f, 1.000000000f };
	const Vect IndianRed = { 0.803921640f, 0.360784322f, 0.360784322f, 1.000000000f };
	const Vect Indigo = { 0.294117659f, 0.000000000f, 0.509803951f, 1.000000000f };
	const Vect Ivory = { 1.000000000f, 1.000000000f, 0.941176534f, 1.000000000f };
	const Vect Khaki = { 0.941176534f, 0.901960850f, 0.549019635f, 1.000000000f };
	const Vect Lavender = { 0.901960850f, 0.901960850f, 0.980392218f, 1.000000000f };
	const Vect LavenderBlush = { 1.000000000f, 0.941176534f, 0.960784376f, 1.000000000f };
	const Vect LawnGreen = { 0.486274540f, 0.988235354f, 0.000000000f, 1.000000000f };
	const Vect LemonChiffon = { 1.000000000f, 0.980392218f, 0.803921640f, 1.000000000f };
	const Vect LightBlue = { 0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f };
	const Vect LightCoral = { 0.941176534f, 0.501960814f, 0.501960814f, 1.000000000f };
	const Vect LightCyan = { 0.878431439f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vect LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f, 1.000000000f };
	const Vect LightGreen = { 0.564705908f, 0.933333397f, 0.564705908f, 1.000000000f };
	const Vect LightGray = { 0.827451050f, 0.827451050f, 0.827451050f, 1.000000000f };
	const Vect LightPink = { 1.000000000f, 0.713725507f, 0.756862819f, 1.000000000f };
	const Vect LightSalmon = { 1.000000000f, 0.627451003f, 0.478431404f, 1.000000000f };
	const Vect LightSeaGreen = { 0.125490203f, 0.698039234f, 0.666666687f, 1.000000000f };
	const Vect LightSkyBlue = { 0.529411793f, 0.807843208f, 0.980392218f, 1.000000000f };
	const Vect LightSlateGray = { 0.466666698f, 0.533333361f, 0.600000024f, 1.000000000f };
	const Vect LightSteelBlue = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f };
	const Vect LightYellow = { 1.000000000f, 1.000000000f, 0.878431439f, 1.000000000f };
	const Vect Lime = { 0.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
	const Vect LimeGreen = { 0.196078449f, 0.803921640f, 0.196078449f, 1.000000000f };
	const Vect Linen = { 0.980392218f, 0.941176534f, 0.901960850f, 1.000000000f };
	const Vect Magenta = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	const Vect Maroon = { 0.501960814f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vect MediumAquamarine = { 0.400000036f, 0.803921640f, 0.666666687f, 1.000000000f };
	const Vect MediumBlue = { 0.000000000f, 0.000000000f, 0.803921640f, 1.000000000f };
	const Vect MediumOrchid = { 0.729411781f, 0.333333343f, 0.827451050f, 1.000000000f };
	const Vect MediumPurple = { 0.576470613f, 0.439215720f, 0.858823597f, 1.000000000f };
	const Vect MediumSeaGreen = { 0.235294133f, 0.701960802f, 0.443137288f, 1.000000000f };
	const Vect MediumSlateBlue = { 0.482352972f, 0.407843173f, 0.933333397f, 1.000000000f };
	const Vect MediumSpringGreen = { 0.000000000f, 0.980392218f, 0.603921592f, 1.000000000f };
	const Vect MediumTurquoise = { 0.282352954f, 0.819607913f, 0.800000072f, 1.000000000f };
	const Vect MediumVioletRed = { 0.780392230f, 0.082352944f, 0.521568656f, 1.000000000f };
	const Vect MidnightBlue = { 0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f };
	const Vect MintCream = { 0.960784376f, 1.000000000f, 0.980392218f, 1.000000000f };
	const Vect MistyRose = { 1.000000000f, 0.894117713f, 0.882353008f, 1.000000000f };
	const Vect Moccasin = { 1.000000000f, 0.894117713f, 0.709803939f, 1.000000000f };
	const Vect NavajoWhite = { 1.000000000f, 0.870588303f, 0.678431392f, 1.000000000f };
	const Vect Navy = { 0.000000000f, 0.000000000f, 0.501960814f, 1.000000000f };
	const Vect OldLace = { 0.992156923f, 0.960784376f, 0.901960850f, 1.000000000f };
	const Vect Olive = { 0.501960814f, 0.501960814f, 0.000000000f, 1.000000000f };
	const Vect OliveDrab = { 0.419607878f, 0.556862772f, 0.137254909f, 1.000000000f };
	const Vect Orange = { 1.000000000f, 0.647058845f, 0.000000000f, 1.000000000f };
	const Vect OrangeRed = { 1.000000000f, 0.270588249f, 0.000000000f, 1.000000000f };
	const Vect Orchid = { 0.854902029f, 0.439215720f, 0.839215755f, 1.000000000f };
	const Vect PaleGoldenrod = { 0.933333397f, 0.909803987f, 0.666666687f, 1.000000000f };
	const Vect PaleGreen = { 0.596078455f, 0.984313786f, 0.596078455f, 1.000000000f };
	const Vect PaleTurquoise = { 0.686274529f, 0.933333397f, 0.933333397f, 1.000000000f };
	const Vect PaleVioletRed = { 0.858823597f, 0.439215720f, 0.576470613f, 1.000000000f };
	const Vect PapayaWhip = { 1.000000000f, 0.937254965f, 0.835294187f, 1.000000000f };
	const Vect PeachPuff = { 1.000000000f, 0.854902029f, 0.725490212f, 1.000000000f };
	const Vect Peru = { 0.803921640f, 0.521568656f, 0.247058839f, 1.000000000f };
	const Vect Pink = { 1.000000000f, 0.752941251f, 0.796078503f, 1.000000000f };
	const Vect Plum = { 0.866666734f, 0.627451003f, 0.866666734f, 1.000000000f };
	const Vect PowderBlue = { 0.690196097f, 0.878431439f, 0.901960850f, 1.000000000f };
	const Vect Purple = { 0.501960814f, 0.000000000f, 0.501960814f, 1.000000000f };
	const Vect Red = { 1.000000000f, 0.000000000f, 0.000000000f, 1.000000000f };
	const Vect RosyBrown = { 0.737254918f, 0.560784340f, 0.560784340f, 1.000000000f };
	const Vect RoyalBlue = { 0.254901975f, 0.411764741f, 0.882353008f, 1.000000000f };
	const Vect SaddleBrown = { 0.545098066f, 0.270588249f, 0.074509807f, 1.000000000f };
	const Vect Salmon = { 0.980392218f, 0.501960814f, 0.447058856f, 1.000000000f };
	const Vect SandyBrown = { 0.956862807f, 0.643137276f, 0.376470625f, 1.000000000f };
	const Vect SeaGreen = { 0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f };
	const Vect SeaShell = { 1.000000000f, 0.960784376f, 0.933333397f, 1.000000000f };
	const Vect Sienna = { 0.627451003f, 0.321568638f, 0.176470593f, 1.000000000f };
	const Vect Silver = { 0.752941251f, 0.752941251f, 0.752941251f, 1.000000000f };
	const Vect SkyBlue = { 0.529411793f, 0.807843208f, 0.921568692f, 1.000000000f };
	const Vect SlateBlue = { 0.415686309f, 0.352941185f, 0.803921640f, 1.000000000f };
	const Vect SlateGray = { 0.439215720f, 0.501960814f, 0.564705908f, 1.000000000f };
	const Vect Snow = { 1.000000000f, 0.980392218f, 0.980392218f, 1.000000000f };
	const Vect SpringGreen = { 0.000000000f, 1.000000000f, 0.498039246f, 1.000000000f };
	const Vect SteelBlue = { 0.274509817f, 0.509803951f, 0.705882370f, 1.000000000f };
	const Vect Tan = { 0.823529482f, 0.705882370f, 0.549019635f, 1.000000000f };
	const Vect Teal = { 0.000000000f, 0.501960814f, 0.501960814f, 1.000000000f };
	const Vect Thistle = { 0.847058892f, 0.749019623f, 0.847058892f, 1.000000000f };
	const Vect Tomato = { 1.000000000f, 0.388235331f, 0.278431386f, 1.000000000f };
	const Vect Transparent = { 0.000000000f, 0.000000000f, 0.000000000f, 0.000000000f };
	const Vect Turquoise = { 0.250980407f, 0.878431439f, 0.815686345f, 1.000000000f };
	const Vect Violet = { 0.933333397f, 0.509803951f, 0.933333397f, 1.000000000f };
	const Vect Wheat = { 0.960784376f, 0.870588303f, 0.701960802f, 1.000000000f };
	const Vect White = { 1.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	const Vect WhiteSmoke = { 0.960784376f, 0.960784376f, 0.960784376f, 1.000000000f };
	const Vect Yellow = { 1.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
	const Vect YellowGreen = { 0.603921592f, 0.803921640f, 0.196078449f, 1.000000000f };

}; // namespace Colors





#endif // D3DUTIL_H