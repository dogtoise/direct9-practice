#if 0

//listing of all techniques and passes with embedded asm listings 

technique Default_Technique
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
            //   sampler2D BaseSampler;
            //   float4 Diffuse;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   Diffuse      c0       1
            //   BaseSampler  s0       1
            //
            
                ps_3_0
                dcl_texcoord v0.xy
                dcl_2d s0
                texld r0, v0, s0
                add_sat oC0, r0, c0
            
            // approximately 2 instruction slots used (1 texture, 1 arithmetic)
            };
    }
}

technique Alpha_Technique
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
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   ProjMatrix   c0       4
            //
            
                vs_3_0
                dcl_position v0
                dcl_texcoord v1
                dcl_position o0
                dcl_texcoord o1.xy
                dp4 o0.x, v0, c0
                dp4 o0.y, v0, c1
                dp4 o0.z, v0, c2
                dp4 o0.w, v0, c3
                mov o1.xy, v1
            
            // approximately 5 instruction slots used
            };

        pixelshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
            //
            // Parameters:
            //
            //   sampler2D BaseSampler;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   BaseSampler  s0       1
            //
            
                ps_3_0
                dcl_texcoord v0.xy
                dcl_2d s0
                texld r0, v0, s0
                mov oC0, r0.w
            
            // approximately 2 instruction slots used (1 texture, 1 arithmetic)
            };
    }
}

technique Gauss_Technique
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
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   ProjMatrix   c0       4
            //
            
                vs_3_0
                dcl_position v0
                dcl_texcoord v1
                dcl_position o0
                dcl_texcoord o1.xy
                dp4 o0.x, v0, c0
                dp4 o0.y, v0, c1
                dp4 o0.z, v0, c2
                dp4 o0.w, v0, c3
                mov o1.xy, v1
            
            // approximately 5 instruction slots used
            };

        pixelshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
            //
            // Parameters:
            //
            //   sampler2D BaseSampler;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   BaseSampler  s0       1
            //
            
                ps_3_0
                dcl_texcoord v0.xy
                dcl_2d s0
                texld oC0, v0, s0
            
            // approximately 1 instruction slot used (1 texture, 0 arithmetic)
            };
    }
}

technique Merge_Technique
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
            //   sampler2D DefaultSampler;
            //   float4 Diffuse;
            //
            //
            // Registers:
            //
            //   Name           Reg   Size
            //   -------------- ----- ----
            //   Diffuse        c0       1
            //   DefaultSampler s0       1
            //
            
                ps_3_0
                dcl_texcoord v0.xy
                dcl_2d s0
                texld r0, v0, s0
                add_sat oC0, r0, c0
            
            // approximately 2 instruction slots used (1 texture, 1 arithmetic)
            };
    }
}

#endif

const BYTE g_MultiRender[] =
{
      1,   9, 255, 254, 168,   6, 
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
     66,  97, 115, 101,  77,  97, 
    112,   0,  10,   0,   0,   0, 
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
     12,   0,   0,   0,  66,  97, 
    115, 101,  83,  97, 109, 112, 
    108, 101, 114,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    252,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  11,   0, 
      0,   0,  68, 101, 102,  97, 
    117, 108, 116,  77,  97, 112, 
      0,   0,  10,   0,   0,   0, 
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
     15,   0,   0,   0,  68, 101, 
    102,  97, 117, 108, 116,  83, 
     97, 109, 112, 108, 101, 114, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 104,   4, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,   9,   0,   0,   0, 
     65, 108, 112, 104,  97,  77, 
     97, 112,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   4,   5,   0,   0, 
      0,   0,   0,   0,   7,   0, 
      0,   0,   4,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
     64, 192,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    128,  60,   0,   0,   0, 192, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 192,  61, 
      0,   0, 128, 191,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 112,  62,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    160,  62,   0,   0, 128,  63, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 112,  62, 
      0,   0,   0,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 192,  61,   0,   0, 
     64,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    128,  60,  12,   0,   0,   0, 
    103,  97, 117, 115, 115,  70, 
    105, 108, 116, 101, 114,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  52,   5,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,  60,  10,   0,   0,   0, 
    116, 101, 120,  83,  99,  97, 
    108, 101, 114,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0, 100,   5,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  10,   0,   0,   0, 
    116, 101, 120,  79, 102, 102, 
    115, 101, 116,   0,   0,   0, 
      6,   0,   0,   0,  16,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   0,   0,   0,  15,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  80,  48, 
      0,   0,  18,   0,   0,   0, 
     68, 101, 102,  97, 117, 108, 
    116,  95,  84, 101,  99, 104, 
    110, 105, 113, 117, 101,   0, 
      0,   0,   8,   0,   0,   0, 
     16,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   9,   0,   0,   0, 
     15,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     80,  48,   0,   0,  16,   0, 
      0,   0,  65, 108, 112, 104, 
     97,  95,  84, 101,  99, 104, 
    110, 105, 113, 117, 101,   0, 
     10,   0,   0,   0,  16,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     11,   0,   0,   0,  15,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  80,  48, 
      0,   0,  16,   0,   0,   0, 
     71,  97, 117, 115, 115,  95, 
     84, 101,  99, 104, 110, 105, 
    113, 117, 101,   0,  12,   0, 
      0,   0,  16,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      0,   0,  15,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  80,  48,   0,   0, 
     16,   0,   0,   0,  77, 101, 
    114, 103, 101,  95,  84, 101, 
     99, 104, 110, 105, 113, 117, 
    101,   0,  12,   0,   0,   0, 
      4,   0,   0,   0,  14,   0, 
      0,   0,  14,   0,   0,   0, 
      4,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 112,   0, 
      0,   0, 140,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 220,   0,   0,   0, 
    248,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     72,   1,   0,   0, 100,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,   1, 
      0,   0, 148,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 164,   1,   0,   0, 
    112,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    228,   2,   0,   0, 248,   2, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  12,   3, 
      0,   0, 216,   3,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  80,   4,   0,   0, 
    100,   4,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    120,   4,   0,   0, 148,   4, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  20,   5, 
      0,   0,  48,   5,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  68,   5,   0,   0, 
     96,   5,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    172,   5,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
    164,   5,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
    146,   0,   0,   0,   0,   0, 
      0,   0, 120,   5,   0,   0, 
    116,   5,   0,   0, 147,   0, 
      0,   0,   0,   0,   0,   0, 
    144,   5,   0,   0, 140,   5, 
      0,   0, 252,   5,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0, 244,   5,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0, 146,   0,   0,   0, 
      0,   0,   0,   0, 200,   5, 
      0,   0, 196,   5,   0,   0, 
    147,   0,   0,   0,   0,   0, 
      0,   0, 224,   5,   0,   0, 
    220,   5,   0,   0,  72,   6, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  64,   6, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0, 146,   0, 
      0,   0,   0,   0,   0,   0, 
     20,   6,   0,   0,  16,   6, 
      0,   0, 147,   0,   0,   0, 
      0,   0,   0,   0,  44,   6, 
      0,   0,  40,   6,   0,   0, 
    148,   6,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
    140,   6,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
    146,   0,   0,   0,   0,   0, 
      0,   0,  96,   6,   0,   0, 
     92,   6,   0,   0, 147,   0, 
      0,   0,   0,   0,   0,   0, 
    120,   6,   0,   0, 116,   6, 
      0,   0,   3,   0,   0,   0, 
     10,   0,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     12,   1,   0,   0,   0,   3, 
    255, 255, 254, 255,  50,   0, 
     67,  84,  65,  66,  28,   0, 
      0,   0, 147,   0,   0,   0, 
      0,   3, 255, 255,   2,   0, 
      0,   0,  28,   0,   0,   0, 
      0, 128,   0,  32, 140,   0, 
      0,   0,  68,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,  84,   0,   0,   0, 
      0,   0,   0,   0, 100,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0, 108,   0, 
      0,   0, 124,   0,   0,   0, 
     68, 101, 102,  97, 117, 108, 
    116,  83,  97, 109, 112, 108, 
    101, 114,   0, 171,   4,   0, 
     12,   0,   1,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  68, 105, 102, 102, 
    117, 115, 101,   0,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
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
     15, 160,  66,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 144,   0,   8, 228, 160, 
      2,   0,   0,   3,   0,   8, 
     31, 128,   0,   0, 228, 128, 
      0,   0, 228, 160, 255, 255, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,  16,   2, 
      0,   0,   0,   3, 254, 255, 
    254, 255,  66,   0,  67,  84, 
     65,  66,  28,   0,   0,   0, 
    210,   0,   0,   0,   0,   3, 
    254, 255,   3,   0,   0,   0, 
     28,   0,   0,   0,   0, 128, 
      0,  32, 203,   0,   0,   0, 
     88,   0,   0,   0,   2,   0, 
      8,   0,   4,   0,   0,   0, 
    100,   0,   0,   0, 116,   0, 
      0,   0, 180,   0,   0,   0, 
      2,   0,   4,   0,   4,   0, 
      0,   0, 100,   0,   0,   0, 
    116,   0,   0,   0, 191,   0, 
      0,   0,   2,   0,   0,   0, 
      4,   0,   0,   0, 100,   0, 
      0,   0, 116,   0,   0,   0, 
     80, 114, 111, 106,  77,  97, 
    116, 114, 105, 120,   0, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   1,   0,   0,   0, 
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
      0,   0,  86, 105, 101, 119, 
     77,  97, 116, 114, 105, 120, 
      0,  87, 111, 114, 108, 100, 
     77,  97, 116, 114, 105, 120, 
      0, 118, 115,  95,  51,  95, 
     48,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      1,   0,  15, 144,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 224,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      1,   0,   3, 224,   9,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0, 228, 144,   0,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   2, 128,   0,   0, 
    228, 144,   1,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      4, 128,   0,   0, 228, 144, 
      2,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 228, 144,   3,   0, 
    228, 160,   9,   0,   0,   3, 
      1,   0,   1, 128,   0,   0, 
    228, 128,   4,   0, 228, 160, 
      9,   0,   0,   3,   1,   0, 
      2, 128,   0,   0, 228, 128, 
      5,   0, 228, 160,   9,   0, 
      0,   3,   1,   0,   4, 128, 
      0,   0, 228, 128,   6,   0, 
    228, 160,   9,   0,   0,   3, 
      1,   0,   8, 128,   0,   0, 
    228, 128,   7,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      1, 224,   1,   0, 228, 128, 
      8,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   2, 224, 
      1,   0, 228, 128,   9,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   4, 224,   1,   0, 
    228, 128,  10,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      8, 224,   1,   0, 228, 128, 
     11,   0, 228, 160,   1,   0, 
      0,   2,   1,   0,   3, 224, 
      1,   0, 228, 144, 255, 255, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   1,   0,   0,   0, 
      0,   0,   0,   0, 188,   0, 
      0,   0,   0,   3, 255, 255, 
    254, 255,  34,   0,  67,  84, 
     65,  66,  28,   0,   0,   0, 
     83,   0,   0,   0,   0,   3, 
    255, 255,   1,   0,   0,   0, 
     28,   0,   0,   0,   0, 128, 
      0,  32,  76,   0,   0,   0, 
     48,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     60,   0,   0,   0,   0,   0, 
      0,   0,  66,  97, 115, 101, 
     83,  97, 109, 112, 108, 101, 
    114,   0,   4,   0,  12,   0, 
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
     15, 160,  66,   0,   0,   3, 
      0,   8,  15, 128,   0,   0, 
    228, 144,   0,   8, 228, 160, 
    255, 255,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     80,   1,   0,   0,   0,   3, 
    254, 255, 254, 255,  50,   0, 
     67,  84,  65,  66,  28,   0, 
      0,   0, 147,   0,   0,   0, 
      0,   3, 254, 255,   1,   0, 
      0,   0,  28,   0,   0,   0, 
      0, 128,   0,  32, 140,   0, 
      0,   0,  48,   0,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0,  60,   0,   0,   0, 
     76,   0,   0,   0,  80, 114, 
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
    118, 115,  95,  51,  95,  48, 
      0,  77, 105,  99, 114, 111, 
    115, 111, 102, 116,  32,  40, 
     82,  41,  32,  72,  76,  83, 
     76,  32,  83, 104,  97, 100, 
    101, 114,  32,  67, 111, 109, 
    112, 105, 108, 101, 114,  32, 
     57,  46,  50,  57,  46,  57, 
     53,  50,  46,  51,  49,  49, 
     49,   0,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 144,  31,   0,   0,   2, 
      5,   0,   0, 128,   1,   0, 
     15, 144,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 224,  31,   0,   0,   2, 
      5,   0,   0, 128,   1,   0, 
      3, 224,   9,   0,   0,   3, 
      0,   0,   1, 224,   0,   0, 
    228, 144,   0,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      2, 224,   0,   0, 228, 144, 
      1,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   4, 224, 
      0,   0, 228, 144,   2,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   8, 224,   0,   0, 
    228, 144,   3,   0, 228, 160, 
      1,   0,   0,   2,   1,   0, 
      3, 224,   1,   0, 228, 144, 
    255, 255,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    200,   0,   0,   0,   0,   3, 
    255, 255, 254, 255,  34,   0, 
     67,  84,  65,  66,  28,   0, 
      0,   0,  83,   0,   0,   0, 
      0,   3, 255, 255,   1,   0, 
      0,   0,  28,   0,   0,   0, 
      0, 128,   0,  32,  76,   0, 
      0,   0,  48,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,  60,   0,   0,   0, 
      0,   0,   0,   0,  66,  97, 
    115, 101,  83,  97, 109, 112, 
    108, 101, 114,   0,   4,   0, 
     12,   0,   1,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 112, 115,  95,  51, 
     95,  48,   0,  77, 105,  99, 
    114, 111, 115, 111, 102, 116, 
     32,  40,  82,  41,  32,  72, 
     76,  83,  76,  32,  83, 104, 
     97, 100, 101, 114,  32,  67, 
    111, 109, 112, 105, 108, 101, 
    114,  32,  57,  46,  50,  57, 
     46,  57,  53,  50,  46,  51, 
     49,  49,  49,   0,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      0,   0,   3, 144,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      0,   8,  15, 160,  66,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 144,   0,   8, 
    228, 160,   1,   0,   0,   2, 
      0,   8,  15, 128,   0,   0, 
    255, 128, 255, 255,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  80,   1,   0,   0, 
      0,   3, 254, 255, 254, 255, 
     50,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 147,   0, 
      0,   0,   0,   3, 254, 255, 
      1,   0,   0,   0,  28,   0, 
      0,   0,   0, 128,   0,  32, 
    140,   0,   0,   0,  48,   0, 
      0,   0,   2,   0,   0,   0, 
      4,   0,   0,   0,  60,   0, 
      0,   0,  76,   0,   0,   0, 
     80, 114, 111, 106,  77,  97, 
    116, 114, 105, 120,   0, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   1,   0,   0,   0, 
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
      0,   0, 118, 115,  95,  51, 
     95,  48,   0,  77, 105,  99, 
    114, 111, 115, 111, 102, 116, 
     32,  40,  82,  41,  32,  72, 
     76,  83,  76,  32,  83, 104, 
     97, 100, 101, 114,  32,  67, 
    111, 109, 112, 105, 108, 101, 
    114,  32,  57,  46,  50,  57, 
     46,  57,  53,  50,  46,  51, 
     49,  49,  49,   0,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      1,   0,  15, 144,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 224,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      1,   0,   3, 224,   9,   0, 
      0,   3,   0,   0,   1, 224, 
      0,   0, 228, 144,   0,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   2, 224,   0,   0, 
    228, 144,   1,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      4, 224,   0,   0, 228, 144, 
      2,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   8, 224, 
      0,   0, 228, 144,   3,   0, 
    228, 160,   1,   0,   0,   2, 
      1,   0,   3, 224,   1,   0, 
    228, 144, 255, 255,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   8,   1,   0,   0, 
      0,   3, 255, 255, 254, 255, 
     49,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 143,   0, 
      0,   0,   0,   3, 255, 255, 
      2,   0,   0,   0,  28,   0, 
      0,   0,   0, 128,   0,  32, 
    136,   0,   0,   0,  68,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  80,   0, 
      0,   0,   0,   0,   0,   0, 
     96,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
    104,   0,   0,   0, 120,   0, 
      0,   0,  66,  97, 115, 101, 
     83,  97, 109, 112, 108, 101, 
    114,   0,   4,   0,  12,   0, 
      1,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     68, 105, 102, 102, 117, 115, 
    101,   0,   1,   0,   3,   0, 
      1,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
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
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,   3, 144, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
     66,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 144, 
      0,   8, 228, 160,   2,   0, 
      0,   3,   0,   8,  31, 128, 
      0,   0, 228, 128,   0,   0, 
    228, 160, 255, 255,   0,   0, 
      0,   0,   0,   0,   0,   0, 
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
    255, 255, 255, 255,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  11,   0,   0,   0, 
     68, 101, 102,  97, 117, 108, 
    116,  77,  97, 112,   0,   0, 
    255, 255, 255, 255,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     66,  97, 115, 101,  77,  97, 
    112,   0
};
