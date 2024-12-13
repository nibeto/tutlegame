xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 82;
 0.19205;-10.88057;-0.00000;,
 -1.95723;-10.93818;-2.14961;,
 0.19205;-10.88057;-3.04000;,
 -2.84749;-10.96203;0.00000;,
 -1.95723;-10.93818;2.14961;,
 0.19205;-10.88057;3.04000;,
 2.34133;-10.82295;2.14961;,
 3.23159;-10.79910;-0.00000;,
 2.34133;-10.82295;-2.14961;,
 -2.16387;-10.85486;-2.35526;,
 0.19104;-10.79175;-3.33084;,
 -3.13930;-10.88101;0.00000;,
 -2.16387;-10.85486;2.35526;,
 0.19104;-10.79175;3.33084;,
 2.54595;-10.72862;2.35526;,
 3.52137;-10.70247;-0.00000;,
 2.54595;-10.72862;-2.35526;,
 -2.34106;-10.60659;-2.52961;,
 0.18817;-10.53879;-3.57740;,
 -3.38870;-10.63467;0.00000;,
 -2.34106;-10.60659;2.52961;,
 0.18816;-10.53879;3.57740;,
 2.71738;-10.47100;2.52961;,
 3.76502;-10.44292;-0.00000;,
 2.71738;-10.47100;-2.52961;,
 -2.46184;-10.23115;-2.64610;,
 0.18386;-10.16022;-3.74215;,
 -3.55773;-10.26052;0.00000;,
 -2.46184;-10.23115;2.64610;,
 0.18386;-10.16022;3.74215;,
 2.82956;-10.08931;2.64610;,
 3.92544;-10.05994;-0.00000;,
 2.82956;-10.08931;-2.64610;,
 -2.50782;-9.78569;-2.68701;,
 0.17878;-9.71368;-3.80000;,
 -3.62064;-9.81551;0.00000;,
 -2.50782;-9.78569;2.68701;,
 0.17878;-9.71368;3.80000;,
 2.86538;-9.64167;2.68701;,
 3.97821;-9.61184;-0.00000;,
 2.86538;-9.64167;-2.68701;,
 -2.61393;-0.45058;-2.68701;,
 0.07267;-0.37856;-3.80000;,
 -3.72675;-0.48041;0.00000;,
 -2.61393;-0.45058;2.68701;,
 0.07267;-0.37856;3.80000;,
 2.75927;-0.30656;2.68701;,
 3.87210;-0.27673;-0.00000;,
 2.75927;-0.30656;-2.68701;,
 -2.57810;-0.00293;-2.64610;,
 0.06759;0.06798;-3.74215;,
 -3.67399;-0.03231;0.00000;,
 -2.57810;-0.00293;2.64610;,
 0.06759;0.06798;3.74215;,
 2.71329;0.13890;2.64610;,
 3.80918;0.16827;-0.00000;,
 2.71329;0.13890;-2.64610;,
 -2.46593;0.37876;-2.52961;,
 0.06329;0.44655;-3.57740;,
 -3.51356;0.35066;0.00000;,
 -2.46593;0.37876;2.52961;,
 0.06329;0.44655;3.57740;,
 2.59251;0.51434;2.52961;,
 3.64015;0.54242;-0.00000;,
 2.59251;0.51434;-2.52961;,
 -2.29449;0.63637;-2.35526;,
 0.06042;0.69950;-3.33084;,
 -3.26992;0.61024;0.00000;,
 -2.29449;0.63637;2.35526;,
 0.06042;0.69950;3.33084;,
 2.41532;0.76262;2.35526;,
 3.39076;0.78877;-0.00000;,
 2.41532;0.76262;-2.35526;,
 -2.08987;0.73071;-2.14961;,
 0.05941;0.78832;-3.04000;,
 -2.98013;0.70685;0.00000;,
 -2.08987;0.73071;2.14961;,
 0.05941;0.78832;3.04000;,
 2.20869;0.84593;2.14961;,
 3.09894;0.86980;-0.00000;,
 2.20869;0.84593;-2.14961;,
 0.05941;0.78832;0.00000;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  1;
  88;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.964706;0.964706;0.964706;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.144706;0.144706;0.144706;;
  }
 }
 MeshNormals {
  82;
  0.026795;-0.999641;-0.000000;,
  0.026396;-0.988766;-0.147119;,
  -0.077847;-0.991495;-0.104299;,
  -0.121181;-0.992630;-0.000000;,
  -0.077847;-0.991495;0.104299;,
  0.026396;-0.988766;0.147119;,
  0.130103;-0.986056;0.103761;,
  0.172901;-0.984939;-0.000000;,
  0.130103;-0.986056;-0.103761;,
  0.022389;-0.855968;-0.516545;,
  -0.344362;-0.864173;-0.366906;,
  -0.497251;-0.867607;0.000000;,
  -0.344362;-0.864173;0.366906;,
  0.022389;-0.855967;0.516545;,
  0.385862;-0.847874;0.363621;,
  0.535473;-0.844552;-0.000000;,
  0.385863;-0.847874;-0.363621;,
  0.014157;-0.559385;-0.828787;,
  -0.574253;-0.569063;-0.588558;,
  -0.819477;-0.573112;0.000000;,
  -0.574253;-0.569063;0.588558;,
  0.014157;-0.559385;0.828787;,
  0.597587;-0.549844;0.583576;,
  0.837830;-0.545931;-0.000000;,
  0.597587;-0.549844;-0.583576;,
  0.006620;-0.267042;-0.963662;,
  -0.676325;-0.275725;-0.683052;,
  -0.960192;-0.279339;0.000000;,
  -0.676325;-0.275724;0.683052;,
  0.006620;-0.267042;0.963662;,
  0.686336;-0.258425;0.679823;,
  0.966974;-0.254876;-0.000000;,
  0.686336;-0.258425;-0.679823;,
  0.001582;-0.064395;-0.997923;,
  -0.704409;-0.072501;-0.706082;,
  -0.997118;-0.075862;0.000000;,
  -0.704409;-0.072501;0.706082;,
  0.001583;-0.064395;0.997923;,
  0.706730;-0.056301;0.705239;,
  0.998597;-0.052953;0.000000;,
  0.706730;-0.056301;-0.705240;,
  -0.001583;0.064394;-0.997923;,
  -0.706731;0.056297;-0.705239;,
  -0.998597;0.052947;0.000000;,
  -0.706731;0.056297;0.705239;,
  -0.001583;0.064394;0.997923;,
  0.704408;0.072503;0.706082;,
  0.997118;0.075866;0.000000;,
  0.704408;0.072503;-0.706082;,
  -0.006620;0.267044;-0.963662;,
  -0.686336;0.258427;-0.679822;,
  -0.966973;0.254879;0.000000;,
  -0.686336;0.258428;0.679822;,
  -0.006620;0.267043;0.963662;,
  0.676324;0.275729;0.683052;,
  0.960190;0.279346;-0.000000;,
  0.676324;0.275729;-0.683052;,
  -0.014155;0.559389;-0.828784;,
  -0.597588;0.549847;-0.583573;,
  -0.837832;0.545929;-0.000000;,
  -0.597587;0.549847;0.583573;,
  -0.014155;0.559389;0.828784;,
  0.574256;0.569059;0.588559;,
  0.819482;0.573105;-0.000000;,
  0.574256;0.569059;-0.588559;,
  -0.022391;0.855967;-0.516545;,
  -0.385866;0.847871;-0.363625;,
  -0.535480;0.844548;-0.000000;,
  -0.385865;0.847871;0.363624;,
  -0.022391;0.855969;0.516543;,
  0.344365;0.864172;0.366907;,
  0.497259;0.867602;-0.000000;,
  0.344365;0.864171;-0.366908;,
  -0.026398;0.988766;-0.147122;,
  -0.130102;0.986056;-0.103764;,
  -0.172898;0.984940;-0.000000;,
  -0.130102;0.986056;0.103764;,
  -0.026398;0.988766;0.147120;,
  0.077844;0.991495;0.104297;,
  0.121177;0.992631;-0.000000;,
  0.077844;0.991495;-0.104298;,
  -0.026795;0.999641;0.000000;;
  88;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;;
 }
 MeshTextureCoords {
  82;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
