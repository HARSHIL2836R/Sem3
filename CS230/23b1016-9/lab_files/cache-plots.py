import matplotlib.pyplot as plt

cache = [4096,8192,16384,32768,65536,131072,262144,524288]
cc1_out = [0.1217,0.0823,0.0478,0.0263,0.0180
,0.0151
,0.0134
,0.0126]
spice_out = [
0.0641
,0.0359
,0.0151
,0.0069
,0.0042
,0.0038
,0.0038
,0.0038]
tex_out = [
0.0051
,0.0049
,0.0035
,0.0029
,0.0029
,0.0029
,0.0029
,0.0029
]

plt.figure(figsize=(14,10))

plt.plot(cache,cc1_out, label='cc1.din')
plt.plot(cache,spice_out, label='spice.din')
plt.plot(cache,tex_out, label='tex.din')
plt.xticks(cache, rotation=90)
plt.xlabel('Cache Size in Bytes')
plt.ylabel('Miss Rate')
plt.title('Miss Rate vs Cache Size')
plt.legend()
plt.savefig('cache-size-plot.png')

plt.clf()

block_size = [4,8,16,32,64,128,256,512,1024]
tex_out = [
0.0183
,0.0092
,0.0049
,0.0027
,0.0019
,0.0030
,0.0053
,0.0145
,0.0396]
spice_out = [
0.0729
,0.0497
,0.0359
,0.0276
,0.0266
,0.0251
,0.0254
,0.0338
,0.0430]
cc1_out = [
0.1968
,0.1214
,0.0823
,0.0600
,0.0485
,0.0430
,0.0417
,0.0468
,0.0644
]

plt.plot(block_size,cc1_out, label='cc1.din')
plt.plot(block_size,spice_out, label='spice.din')
plt.plot(block_size,tex_out, label='tex.din')
plt.xticks(block_size, rotation=90)
plt.xlabel('Block Size in Bytes')
plt.ylabel('Miss Rate')
plt.title('Miss Rate vs Block Size')
plt.legend()

plt.savefig('block-size-plot.png')

plt.clf()

assoc = [1,2,4,8,16,32,64,128,256,512]
tex_out = [
0.0064
,0.0049
,0.0046
,0.0046
,0.0046
,0.0046
,0.0046
,0.0046
,0.0046
,0.0046
]
spice_out = [
0.0574
,0.0359
,0.0275
,0.0242
,0.0246
,0.0257
,0.0263
,0.0261
,0.0259
,0.0260
]
cc1_out = [
0.1012
,0.0823
,0.0733
,0.0706
,0.0691
,0.0693
,0.0692
,0.0688
,0.0688
,0.0688
]
plt.plot(assoc,cc1_out, label='cc1.din')
plt.plot(assoc,spice_out, label='spice.din')
plt.plot(assoc,tex_out, label='tex.din')
plt.xticks(assoc, rotation=90)
plt.xlabel('Associativity')
plt.ylabel('Miss Rate')
plt.title('Miss Rate vs Associativity')
plt.legend()

plt.savefig('assoc-plot.png')