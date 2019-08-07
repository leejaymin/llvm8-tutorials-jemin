# LLVM-8.0.0 Tutorials #
---

## Prerequisite ##

### 소스코드 다운후 빌드해서 설치하는 방법 ###

Download source files
- LLVM source code
- Clang source code

unzip and rename
```bash
tar xf llvm-8.0.0.src.tar.xz
tar xf cfe.8.0.0.src.tar.xz
mv llvm-8.0.0.src llvm # 반드시 이름을 llvm으로 한다.

# move to llvm/tools directory
mv cfe-8.0.0.src clang
mv clang ./llvm/tools/

# llvm 디렉터리 밖에서 llvm-objects 디렉터리 생성
mkdir llvm-objects
cmake ../llvm && make -j4
cmake -DCMAKE_INSTALL_PREFIX=../llvm-install/ -P cmake_install.cmake
```

### setting for environment variables
```bash
export LLVM_BASE_DIR=/home/jemin/development/llvm/

export LLVM_DIR=${LLVM_BASE_DIR}
export LLVM_SRC=${LLVM_BASE_DIR}/llvm
export LLVM_SRC_ROOT=${LLVM_BASE_DIR}/llvm
export LLVM_ROOT=${LLVM_BASE_DIR}/llvm
export LLVM_OBJ=${LLVM_BASE_DIR}/llvm-objects
export LLVM_OBJ_DIR=${LLVM_BASE_DIR}/llvm-objects
export LLVM_OBJ_ROOT=${LLVM_BASE_DIR}/llvm-objects
export LLVM_INSTALL_DIR=${LLVM_BASE_DIR}/llvm-install
export PATH=$LLVM_INSTALL_DIR/bin:$PATH
```



## Day-1 ##

### IR Optimization (Part I)

![스크린샷 2019-04-10 오후 10.55.42](https://i.imgur.com/NP6XaeW.png)
- 소스코드 [NamePrinter 소스](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/NamePrinter)
- 실행방법 및 결과
```bash
make clean && make
clang -c -emit-llvm test.c -o test.bc
opt -load ./NamePrinter.so -NamePrinter test.bc -o test.opt.bc
Hello: main
Hello: add
```

![스크린샷 2019-04-10 오후 11.02.06](https://i.imgur.com/8fb8M94.png)
- 소스코드 [InstCount](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/InstCount)
- 실행 방법
 ```bash
make clean && make
clang -c -emit-llvm test.c -o test.bc
opt -load ./InstCount.so -InstCount test.bc -o test.opt.bc
```
- 실행 결과
```bash
Function name: main
14
Function name: add
8
```

![스크린샷 2019-04-10 오후 11.02.34](https://i.imgur.com/mtmEvMN.png)
- 소스코드 [CallCount](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/CallCount)
- 실행 방법
 ```bash
make clean && make
clang -c -emit-llvm test.c -o test.bc

opt -load ./CallCount.so -CallCount test.bc -o test.opt.bc
 ```
- 실행 결과
 ```bash
printf
add
printf
 ```


![스크린샷 2019-04-10 오후 11.02.56](https://i.imgur.com/TpUtGze.png)
- 소스코드 [LoopAnalysis](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/LoopAnalysis)
- 실행 방법
```bash
make clean && make

clang -c -emit-llvm test.c -O3 test.bc

opt -load ./MyLoopAnalysis.so -MyLoopAnalysis test.bc -o test.opt.bc

opt -load ./MyLoopAnalysis.so -MyLoopAnalysis test.bc -o test.opt.bc
```
> - `O3`로 컴파일해야 Loop에 대한 정보가 자세히 기록 되어서 분석이 잘 된다.
> - test 코드 작성시 루프가 최적화 과정에서 사라질 수 있으니 의미 있게 잘 작성 한다.

- 실행 결과
 ```bash
for.cond18.preheader
for.cond3.preheader
  %indvars.iv85 = phi i64 [ %indvars.iv.next86, %for.inc42 ], [ 0, %for.inc12 ]
  %indvars.iv91 = phi i64 [ 0, %entry ], [ %indvars.iv.next92, %for.inc12 ]
 ```

### IR Optimization (Part 2)

![스크린샷 2019-04-10 오후 11.04.10](https://i.imgur.com/0PlLu6F.png)
- 소스코드 [InsertIncFun](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/InsertIncFun)
- 실행 방법
```bash
clang -c -emit-llvm test.c -o test.bc

llvm-dis test.bc

opt -load ./InsertInc.so -InsertInc test.bc -o test.opt.bc

llvm-dis test.opt.bc  
```
- 실행 결과
아래 두 개의 ll파일을 열어서 IR을 확인해 보면 `@inc`가 `test.opt.ll`의 경우 삽입된 것을 알 수 있다.

```bash
vi test.ll
vi test.opt.ll
```

![스크린샷 2019-04-10 오후 11.04.43](https://i.imgur.com/uhtQ71B.png)
- 소스코드 [Printint](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/PrintInt)
- 실행 방법
 ```bash
clang -c -emit-llvm control.c -o control.bc

opt -load ./Hello.so -helloModule control.bc -o control.opt.bc

clang control.opt.bc -o control.opt.exe

./control.opt.exe   
 ```

- 실행 결과
 ```bash
2
4
 ```

## Day-2

## IR Optimization (Part 2)

![스크린샷 2019-04-12 오전 8.50.24](https://i.imgur.com/62yXO7C.png)
- 소스코드 [DynamicCallCount](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/DynamicCallCount)
- 실행 방법
```bash
# 테스트 C 코드를  .bc 코드로 생성
clang -c -emit-llvm test.c -o test.bc

# runtime function call을 삽입하는 기능을 가진 pass를 테스트 c코드에 연결 시킨다.
opt -load ./DynamicCallCount.so -helloModule test.bc -o test.opt.bc

# 테스트 코드와 런타임 콜의 object를 엮어서 실행파일 생성
clang test.opt.bc ../runtime/callCount.so -o test.opt.exe
```

- 실행 결과
```bash
./test.opt.exe
Hello world!
1 + 2 = 3
Dynamic call count: 5
```

![스크린샷 2019-04-12 오전 8.51.00](https://i.imgur.com/2mwa5Sm.png)
- 소스코드 [InstNamer](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/InstNamer)
- 실행 방법
```bash
make clean && make
clang -c -emit-llvm test.c -o test.bc
opt -load ./namer.so -helloModule test.bc -o test.opt.bc

```
- 실행 결과
```bash
llvm-dis test.bc
llvm-dis test.opt.bc

vi test.ll
vi test.opt.ll
```
`test.opt.ll`파일을 보면   `Instruction`들에 `naming`이 숫자로 순서대로 Naming된 것을 알 수 있다.

### Practice 번외-1: Call count per an instruction

- 소스코드 [DynamicCallCountNamer](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/DynamicCallCountNamer)
- 실행 방법
```bash
clang -c -emit-llvm test.c -o test.bc

opt -load ./DyNamerCallCount.so -helloModule test.bc -o test.opt.bc

clang test.opt.bc ../runtime/InstCallCount.so -o test.opt.exe -lstdc++

```
- 실행 결과
```bash
./test.opt.exe

Hello world!
1 + 2 = 3
Dynamic call count:
1 1
7 4
```


### Practice 번외-2: Instruction Dependence Analysis

- 소스코드 [DependenceAnalysis](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/DependenceAnalysis)
- 실행 방법
```bash
clang -c -emit-llvm test.c -o test.bc
opt -load ./DependenceAnalysis.so -helloFunction test.bc -o test.opt.bc
```

- 실행 결과
```bash
Output:
  store i32 0, i32* %retval, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %2)
Flow:
  store i32 0, i32* %a, align 4
  %0 = load i32, i32* %a, align 4
Output:
  store i32 0, i32* %a, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %2)
Flow:
  store i32 1, i32* %b, align 4
  %1 = load i32, i32* %b, align 4
Output:
  store i32 1, i32* %b, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %2)
Anti:
  %0 = load i32, i32* %a, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %2)
Anti:
  %1 = load i32, i32* %b, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %2)
Flow:
  store i32 %add, i32* %c, align 4
  %2 = load i32, i32* %c, align 4
Output:
  store i32 %add, i32* %c, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %2)
Anti:
  %2 = load i32, i32* %c, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %2)
```

### Practice 번외-3: Alias Analysis

- 소스코드 [AliasAnalysis](https://github.com/leejaymin/llvm8-tutorials-jemin/tree/master/optimization/AliasAnalysis)
- 실행 방법
```bash
clang -c -emit-llvm test.c -o test.bc
opt -load ./AliasAnalysis.so -basicaa -helloFunction test.bc -o test.opt.bc
```
- 실행 결과
```bash
# 1개를 제외하고 모두 NoAlias로 판별
NoAlias:
  %retval = alloca i32, align 4
  %a = alloca [10 x i32], align 16
...
...
May Alias:
  %a = alloca [10 x i32], align 16
  %arrayidx = getelementptr inbounds [10 x i32], [10 x i32]* %a, i64 0, i64 1
NoAlias:
...
```
