# `size_t`:
Unsigned integral type
Alias of one of the fundamental unsigned integer types.

It is a type able to represent the size of any object in bytes: `size_t` is the type returned by the `sizeof` operator and is widely used in the standard library to represent sizes and counts.

# PERFORMANCE:
## Local Vector:
### o0:
1.07825e+10  
2.48169e+09  
1.85642e+09  
2.11458e+09  
2.21373e+09  

### o1:
1.36807e+09  
1.914e+08  
1.57602e+08  
2.61416e+08  
3.77606e+08  

### o2:
1.3082e+09  
1.81623e+08  
1.1622e+08  
2.59892e+08  
3.98719e+08  

### o3:
1.10378e+09  
2.3315e+08  
9.73448e+07  
2.25297e+08  
3.53005e+08  

## Local Array:
### o0:
1.1341e+09  
3.4982e+08  
2.61949e+08  
2.6936e+08  
4.37753e+08  

### o1:
1.00078e+09  
1.7854e+08  
1.67909e+08  
1.70095e+08  
2.89e+08  

### o2:
9.32109e+08  
1.76243e+08  
1.86476e+08  
1.60068e+08  
1.72558e+08  

### o3:
9.08026e+08  
1.30913e+08  
1.06223e+08  
1.09384e+08  
2.25764e+08  

## Global Array:
### o0:
2.12045e+08  
1.65431e+08  
1.51549e+08  
1.65228e+08  
4.07291e+08  

### o1:
6.84121e+07
6.37942e+07
7.34122e+07
7.94221e+07
1.84369e+08

### o2:
4.17253e+07  
2.79857e+07  
3.20068e+07  
1.8846e+07  
1.555e+08  

### o3:
3.16735e+07  
2.25397e+07  
9.70676e+06  
2.02996e+07  
1.1601e+08  


