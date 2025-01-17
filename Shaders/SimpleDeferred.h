#if 0

//listing of all techniques and passes with embedded asm listings 

technique GBuffer
{
    pass P0
    {
        vertexshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
            //
            // Parameters:
            //
            //   float4x4 ProjMatrix;
            //   float4x4 ViewMatrix;
            //   float4x4 WorldMatrix;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   WorldMatrix  c0       4
            //   ViewMatrix   c4       4
            //   ProjMatrix   c8       4
            //
            
                vs_3_0
                dcl_position v0
                dcl_texcoord v1
                dcl_position o0
                dcl_texcoord o1
                dcl_texcoord1 o2.xy
                dp4 r0.x, v0, c0
                dp4 r0.y, v0, c1
                dp4 r0.z, v0, c2
                dp4 r0.w, v0, c3
                dp4 r1.x, r0, c4
                dp4 r1.y, r0, c5
                dp4 r1.z, r0, c6
                dp4 r1.w, r0, c7
                dp4 r0.x, r1, c8
                dp4 r0.y, r1, c9
                dp4 r0.z, r1, c10
                dp4 r0.w, r1, c11
                mov o0, r0
                mov o1, r0
                mov o2.xy, v1
            
            // approximately 15 instruction slots used
            };

        pixelshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
            //
            // Parameters:
            //
            //   float4 Diffuse;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   Diffuse      c0       1
            //
            
                preshader
                mov c0, c0
            
            // approximately 1 instruction used
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
            //
            // Parameters:
            //
            //   sampler2D CubeSampler;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   CubeSampler  s0       1
            //
            
                ps_3_0
                dcl_texcoord v0
                dcl_texcoord1 v1.xy
                dcl_2d s0
                texld oC1, v1, s0
                mov oC0, v0
                mov oC2, c0
            
            // approximately 3 instruction slots used (1 texture, 2 arithmetic)
            };
    }
}

technique OutScreen
{
    pass P0
    {
        vertexshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
            //
            // Parameters:
            //
            //   float4x4 ProjMatrix;
            //   float4x4 ViewMatrix;
            //   float4x4 WorldMatrix;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   WorldMatrix  c0       4
            //   ViewMatrix   c4       4
            //   ProjMatrix   c8       4
            //
            
                vs_3_0
                dcl_position v0
                dcl_texcoord v1
                dcl_position o0
                dcl_texcoord o1.xy
                dp4 r0.x, v0, c0
                dp4 r0.y, v0, c1
                dp4 r0.z, v0, c2
                dp4 r0.w, v0, c3
                dp4 r1.x, r0, c4
                dp4 r1.y, r0, c5
                dp4 r1.z, r0, c6
                dp4 r1.w, r0, c7
                dp4 o0.x, r1, c8
                dp4 o0.y, r1, c9
                dp4 o0.z, r1, c10
                dp4 o0.w, r1, c11
                mov o1.xy, v1
            
            // approximately 13 instruction slots used
            };

        pixelshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
            //
            // Parameters:
            //
            //   sampler2D AlbedoSampler;
            //   sampler2D DiffuseSampler;
            //
            //
            // Registers:
            //
            //   Name           Reg   Size
            //   -------------- ----- ----
            //   AlbedoSampler  s0       1
            //   DiffuseSampler s1       1
            //
            
                ps_3_0
                dcl_texcoord v0.xy
                dcl_2d s0
                dcl_2d s1
                texld r0, v0, s0
                texld r1, v0, s1
                add_sat oC0, r0, r1
            
            // approximately 3 instruction slots used (2 texture, 1 arithmetic)
            };
    }
}

#endif

const BYTE g_SimpleDeferred[] =
{
      1,   9, 255, 254, 180,   7, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,  96,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  12,   0,   0,   0, 
     87, 111, 114, 108, 100,  77, 
     97, 116, 114, 105, 120,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0, 204,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  11,   0,   0,   0, 
     86, 105, 101, 119,  77,  97, 
    116, 114, 105, 120,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,  56,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  11,   0,   0,   0, 
     80, 114, 111, 106,  77,  97, 
    116, 114, 105, 120,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0, 116,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     68, 105, 102, 102, 117, 115, 
    101,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 152,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     67, 117,  98, 101,  84, 101, 
    120,   0,  10,   0,   0,   0, 
      4,   0,   0,   0, 212,   2, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   6,   0,   0,   0, 
    164,   0,   0,   0,   0,   1, 
      0,   0, 188,   1,   0,   0, 
    184,   1,   0,   0, 170,   0, 
      0,   0,   0,   1,   0,   0, 
    212,   1,   0,   0, 208,   1, 
      0,   0, 169,   0,   0,   0, 
      0,   1,   0,   0, 244,   1, 
      0,   0, 240,   1,   0,   0, 
    171,   0,   0,   0,   0,   1, 
      0,   0,  20,   2,   0,   0, 
     16,   2,   0,   0, 165,   0, 
      0,   0,   0,   1,   0,   0, 
     52,   2,   0,   0,  48,   2, 
      0,   0, 166,   0,   0,   0, 
      0,   1,   0,   0,  84,   2, 
      0,   0,  80,   2,   0,   0, 
     12,   0,   0,   0,  67, 117, 
     98, 101,  83,  97, 109, 112, 
    108, 101, 114,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    252,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  12,   0, 
      0,   0,  80, 111, 115, 105, 
    116, 105, 111, 110,  84, 101, 
    120,   0,  10,   0,   0,   0, 
      4,   0,   0,   0,  60,   4, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   6,   0,   0,   0, 
    164,   0,   0,   0,   0,   1, 
      0,   0,  36,   3,   0,   0, 
     32,   3,   0,   0, 170,   0, 
      0,   0,   0,   1,   0,   0, 
     60,   3,   0,   0,  56,   3, 
      0,   0, 169,   0,   0,   0, 
      0,   1,   0,   0,  92,   3, 
      0,   0,  88,   3,   0,   0, 
    171,   0,   0,   0,   0,   1, 
      0,   0, 124,   3,   0,   0, 
    120,   3,   0,   0, 165,   0, 
      0,   0,   0,   1,   0,   0, 
    156,   3,   0,   0, 152,   3, 
      0,   0, 166,   0,   0,   0, 
      0,   1,   0,   0, 188,   3, 
      0,   0, 184,   3,   0,   0, 
     16,   0,   0,   0,  80, 111, 
    115, 105, 116, 105, 111, 110, 
     83,  97, 109, 112, 108, 101, 
    114,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 104,   4, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,  10,   0,   0,   0, 
     65, 108,  98, 101, 100, 111, 
     84, 101, 120,   0,   0,   0, 
     10,   0,   0,   0,   4,   0, 
      0,   0, 168,   5,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      6,   0,   0,   0, 164,   0, 
      0,   0,   0,   1,   0,   0, 
    144,   4,   0,   0, 140,   4, 
      0,   0, 170,   0,   0,   0, 
      0,   1,   0,   0, 168,   4, 
      0,   0, 164,   4,   0,   0, 
    169,   0,   0,   0,   0,   1, 
      0,   0, 200,   4,   0,   0, 
    196,   4,   0,   0, 171,   0, 
      0,   0,   0,   1,   0,   0, 
    232,   4,   0,   0, 228,   4, 
      0,   0, 165,   0,   0,   0, 
      0,   1,   0,   0,   8,   5, 
      0,   0,   4,   5,   0,   0, 
    166,   0,   0,   0,   0,   1, 
      0,   0,  40,   5,   0,   0, 
     36,   5,   0,   0,  14,   0, 
      0,   0,  65, 108,  98, 101, 
    100, 111,  83,  97, 109, 112, 
    108, 101, 114,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 212,   5,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   7,   0,   0,   0, 
     11,   0,   0,   0,  68, 105, 
    102, 102, 117, 115, 101,  84, 
    101, 120,   0,   0,  10,   0, 
      0,   0,   4,   0,   0,   0, 
     20,   7,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   6,   0, 
      0,   0, 164,   0,   0,   0, 
      0,   1,   0,   0, 252,   5, 
      0,   0, 248,   5,   0,   0, 
    170,   0,   0,   0,   0,   1, 
      0,   0,  20,   6,   0,   0, 
     16,   6,   0,   0, 169,   0, 
      0,   0,   0,   1,   0,   0, 
     52,   6,   0,   0,  48,   6, 
      0,   0, 171,   0,   0,   0, 
      0,   1,   0,   0,  84,   6, 
      0,   0,  80,   6,   0,   0, 
    165,   0,   0,   0,   0,   1, 
      0,   0, 116,   6,   0,   0, 
    112,   6,   0,   0, 166,   0, 
      0,   0,   0,   1,   0,   0, 
    148,   6,   0,   0, 144,   6, 
      0,   0,  15,   0,   0,   0, 
     68, 105, 102, 102, 117, 115, 
    101,  83,  97, 109, 112, 108, 
    101, 114,   0,   0,   9,   0, 
      0,   0,  16,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  10,   0, 
      0,   0,  15,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  80,  48,   0,   0, 
      8,   0,   0,   0,  71,  66, 
    117, 102, 102, 101, 114,   0, 
     11,   0,   0,   0,  16,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,  15,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  80,  48, 
      0,   0,  10,   0,   0,   0, 
     79, 117, 116,  83,  99, 114, 
    101, 101, 110,   0,   0,   0, 
     12,   0,   0,   0,   2,   0, 
      0,   0,  10,   0,   0,   0, 
     13,   0,   0,   0,   4,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 112,   0,   0,   0, 
    140,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    220,   0,   0,   0, 248,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  72,   1, 
      0,   0, 100,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128,   1,   0,   0, 
    148,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    164,   1,   0,   0, 112,   2, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 228,   2, 
      0,   0, 248,   2,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  12,   3,   0,   0, 
    216,   3,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     80,   4,   0,   0, 100,   4, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 120,   4, 
      0,   0,  68,   5,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 188,   5,   0,   0, 
    208,   5,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    228,   5,   0,   0, 176,   6, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  96,   7, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  88,   7, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0, 146,   0, 
      0,   0,   0,   0,   0,   0, 
     44,   7,   0,   0,  40,   7, 
      0,   0, 147,   0,   0,   0, 
      0,   0,   0,   0,  68,   7, 
      0,   0,  64,   7,   0,   0, 
    164,   7,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
    156,   7,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
    146,   0,   0,   0,   0,   0, 
      0,   0, 112,   7,   0,   0, 
    108,   7,   0,   0, 147,   0, 
      0,   0,   0,   0,   0,   0, 
    136,   7,   0,   0, 132,   7, 
      0,   0,   4,   0,   0,   0, 
      8,   0,   0,   0,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  32,   1,   0,   0, 
      0,   3, 255, 255, 254, 255, 
     48,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 139,   0, 
      0,   0,   0,   3, 255, 255, 
      2,   0,   0,   0,  28,   0, 
      0,   0,   0, 128,   0,  32, 
    132,   0,   0,   0,  68,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  84,   0, 
      0,   0,   0,   0,   0,   0, 
    100,   0,   0,   0,   3,   0, 
      1,   0,   1,   0,   0,   0, 
    116,   0,   0,   0,   0,   0, 
      0,   0,  65, 108,  98, 101, 
    100, 111,  83,  97, 109, 112, 
    108, 101, 114,   0, 171, 171, 
      4,   0,  12,   0,   1,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  68, 105, 
    102, 102, 117, 115, 101,  83, 
     97, 109, 112, 108, 101, 114, 
      0, 171,   4,   0,  12,   0, 
      1,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    112, 115,  95,  51,  95,  48, 
      0,  77, 105,  99, 114, 111, 
    115, 111, 102, 116,  32,  40, 
     82,  41,  32,  72,  76,  83, 
     76,  32,  83, 104,  97, 100, 
    101, 114,  32,  67, 111, 109, 
    112, 105, 108, 101, 114,  32, 
     57,  46,  50,  57,  46,  57, 
     53,  50,  46,  51,  49,  49, 
     49,   0,  31,   0,   0,   2, 
      5,   0,   0, 128,   0,   0, 
      3, 144,  31,   0,   0,   2, 
      0,   0,   0, 144,   0,   8, 
     15, 160,  31,   0,   0,   2, 
      0,   0,   0, 144,   1,   8, 
     15, 160,  66,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 144,   0,   8, 228, 160, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   0,   0, 228, 144, 
      1,   8, 228, 160,   2,   0, 
      0,   3,   0,   8,  31, 128, 
      0,   0, 228, 128,   1,   0, 
    228, 128, 255, 255,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  16,   2,   0,   0, 
      0,   3, 254, 255, 254, 255, 
     66,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 210,   0, 
      0,   0,   0,   3, 254, 255, 
      3,   0,   0,   0,  28,   0, 
      0,   0,   0, 128,   0,  32, 
    203,   0,   0,   0,  88,   0, 
      0,   0,   2,   0,   8,   0, 
      4,   0,   0,   0, 100,   0, 
      0,   0, 116,   0,   0,   0, 
    180,   0,   0,   0,   2,   0, 
      4,   0,   4,   0,   0,   0, 
    100,   0,   0,   0, 116,   0, 
      0,   0, 191,   0,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0, 100,   0,   0,   0, 
    116,   0,   0,   0,  80, 114, 
    111, 106,  77,  97, 116, 114, 
    105, 120,   0, 171,   3,   0, 
      3,   0,   4,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     86, 105, 101, 119,  77,  97, 
    116, 114, 105, 120,   0,  87, 
    111, 114, 108, 100,  77,  97, 
    116, 114, 105, 120,   0, 118, 
    115,  95,  51,  95,  48,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 144,  31,   0,   0,   2, 
      5,   0,   0, 128,   1,   0, 
     15, 144,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 224,  31,   0,   0,   2, 
      5,   0,   0, 128,   1,   0, 
      3, 224,   9,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
    228, 144,   0,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      2, 128,   0,   0, 228, 144, 
      1,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   4, 128, 
      0,   0, 228, 144,   2,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   8, 128,   0,   0, 
    228, 144,   3,   0, 228, 160, 
      9,   0,   0,   3,   1,   0, 
      1, 128,   0,   0, 228, 128, 
      4,   0, 228, 160,   9,   0, 
      0,   3,   1,   0,   2, 128, 
      0,   0, 228, 128,   5,   0, 
    228, 160,   9,   0,   0,   3, 
      1,   0,   4, 128,   0,   0, 
    228, 128,   6,   0, 228, 160, 
      9,   0,   0,   3,   1,   0, 
      8, 128,   0,   0, 228, 128, 
      7,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   1, 224, 
      1,   0, 228, 128,   8,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   2, 224,   1,   0, 
    228, 128,   9,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      4, 224,   1,   0, 228, 128, 
     10,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   8, 224, 
      1,   0, 228, 128,  11,   0, 
    228, 160,   1,   0,   0,   2, 
      1,   0,   3, 224,   1,   0, 
    228, 144, 255, 255,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 248,   1,   0,   0, 
      0,   3, 255, 255, 254, 255, 
     34,   0,  67,  84,  65,  66, 
     28,   0,   0,   0,  83,   0, 
      0,   0,   0,   3, 255, 255, 
      1,   0,   0,   0,  28,   0, 
      0,   0,   0, 128,   0,  32, 
     76,   0,   0,   0,  48,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
     67, 117,  98, 101,  83,  97, 
    109, 112, 108, 101, 114,   0, 
      4,   0,  12,   0,   1,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 112, 115, 
     95,  51,  95,  48,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  57,  46, 
     50,  57,  46,  57,  53,  50, 
     46,  51,  49,  49,  49,   0, 
    254, 255,  69,   0,  80,  82, 
     69,  83,   1,   2,  88,  70, 
    254, 255,  36,   0,  67,  84, 
     65,  66,  28,   0,   0,   0, 
     91,   0,   0,   0,   1,   2, 
     88,  70,   1,   0,   0,   0, 
     28,   0,   0,   0,   0, 129, 
      0,  32,  88,   0,   0,   0, 
     48,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
     56,   0,   0,   0,  72,   0, 
      0,   0,  68, 105, 102, 102, 
    117, 115, 101,   0,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    116, 120,   0,  77, 105,  99, 
    114, 111, 115, 111, 102, 116, 
     32,  40,  82,  41,  32,  72, 
     76,  83,  76,  32,  83, 104, 
     97, 100, 101, 114,  32,  67, 
    111, 109, 112, 105, 108, 101, 
    114,  32,  57,  46,  50,  57, 
     46,  57,  53,  50,  46,  51, 
     49,  49,  49,   0, 254, 255, 
     12,   0,  80,  82,  83,  73, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 254, 255,   2,   0, 
     67,  76,  73,  84,   0,   0, 
      0,   0, 254, 255,  12,   0, 
     70,  88,  76,  67,   1,   0, 
      0,   0,   4,   0,   0,  16, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0, 240, 240, 
    240, 240,  15,  15,  15,  15, 
    255, 255,   0,   0,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   1, 128, 
      1,   0,   3, 144,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      0,   8,  15, 160,  66,   0, 
      0,   3,   1,   8,  15, 128, 
      1,   0, 228, 144,   0,   8, 
    228, 160,   1,   0,   0,   2, 
      0,   8,  15, 128,   0,   0, 
    228, 144,   1,   0,   0,   2, 
      2,   8,  15, 128,   0,   0, 
    228, 160, 255, 255,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  52,   2,   0,   0, 
      0,   3, 254, 255, 254, 255, 
     66,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 210,   0, 
      0,   0,   0,   3, 254, 255, 
      3,   0,   0,   0,  28,   0, 
      0,   0,   0, 128,   0,  32, 
    203,   0,   0,   0,  88,   0, 
      0,   0,   2,   0,   8,   0, 
      4,   0,   0,   0, 100,   0, 
      0,   0, 116,   0,   0,   0, 
    180,   0,   0,   0,   2,   0, 
      4,   0,   4,   0,   0,   0, 
    100,   0,   0,   0, 116,   0, 
      0,   0, 191,   0,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0, 100,   0,   0,   0, 
    116,   0,   0,   0,  80, 114, 
    111, 106,  77,  97, 116, 114, 
    105, 120,   0, 171,   3,   0, 
      3,   0,   4,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     86, 105, 101, 119,  77,  97, 
    116, 114, 105, 120,   0,  87, 
    111, 114, 108, 100,  77,  97, 
    116, 114, 105, 120,   0, 118, 
    115,  95,  51,  95,  48,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 144,  31,   0,   0,   2, 
      5,   0,   0, 128,   1,   0, 
     15, 144,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 224,  31,   0,   0,   2, 
      5,   0,   0, 128,   1,   0, 
     15, 224,  31,   0,   0,   2, 
      5,   0,   1, 128,   2,   0, 
      3, 224,   9,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
    228, 144,   0,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      2, 128,   0,   0, 228, 144, 
      1,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   4, 128, 
      0,   0, 228, 144,   2,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   8, 128,   0,   0, 
    228, 144,   3,   0, 228, 160, 
      9,   0,   0,   3,   1,   0, 
      1, 128,   0,   0, 228, 128, 
      4,   0, 228, 160,   9,   0, 
      0,   3,   1,   0,   2, 128, 
      0,   0, 228, 128,   5,   0, 
    228, 160,   9,   0,   0,   3, 
      1,   0,   4, 128,   0,   0, 
    228, 128,   6,   0, 228, 160, 
      9,   0,   0,   3,   1,   0, 
      8, 128,   0,   0, 228, 128, 
      7,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   1, 128, 
      1,   0, 228, 128,   8,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   2, 128,   1,   0, 
    228, 128,   9,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      4, 128,   1,   0, 228, 128, 
     10,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   8, 128, 
      1,   0, 228, 128,  11,   0, 
    228, 160,   1,   0,   0,   2, 
      0,   0,  15, 224,   0,   0, 
    228, 128,   1,   0,   0,   2, 
      1,   0,  15, 224,   0,   0, 
    228, 128,   1,   0,   0,   2, 
      2,   0,   3, 224,   1,   0, 
    228, 144, 255, 255,   0,   0, 
    255, 255, 255, 255,  11,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  11,   0,   0,   0, 
     68, 105, 102, 102, 117, 115, 
    101,  84, 101, 120,   0,   0, 
    255, 255, 255, 255,   9,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  10,   0,   0,   0, 
     65, 108,  98, 101, 100, 111, 
     84, 101, 120,   0,   0,   0, 
    255, 255, 255, 255,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  12,   0,   0,   0, 
     80, 111, 115, 105, 116, 105, 
    111, 110,  84, 101, 120,   0, 
    255, 255, 255, 255,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     67, 117,  98, 101,  84, 101, 
    120,   0
};
