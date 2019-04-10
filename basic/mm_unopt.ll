; ModuleID = 'mm.bc'
source_filename = "mm.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  %a = alloca [512 x [512 x i32]], align 16
  %b = alloca [512 x [512 x i32]], align 16
  %c = alloca [512 x [512 x i32]], align 16
  store i32 0, i32* %retval, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc10, %entry
  %0 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %0, 512
  br i1 %cmp, label %for.body, label %for.end12

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc, %for.body
  %1 = load i32, i32* %j, align 4
  %cmp2 = icmp slt i32 %1, 512
  br i1 %cmp2, label %for.body3, label %for.end

for.body3:                                        ; preds = %for.cond1
  %2 = load i32, i32* %i, align 4
  %3 = load i32, i32* %i, align 4
  %idxprom = sext i32 %3 to i64
  %arrayidx = getelementptr inbounds [512 x [512 x i32]], [512 x [512 x i32]]* %a, i64 0, i64 %idxprom
  %4 = load i32, i32* %j, align 4
  %idxprom4 = sext i32 %4 to i64
  %arrayidx5 = getelementptr inbounds [512 x i32], [512 x i32]* %arrayidx, i64 0, i64 %idxprom4
  store i32 %2, i32* %arrayidx5, align 4
  %5 = load i32, i32* %j, align 4
  %6 = load i32, i32* %i, align 4
  %idxprom6 = sext i32 %6 to i64
  %arrayidx7 = getelementptr inbounds [512 x [512 x i32]], [512 x [512 x i32]]* %b, i64 0, i64 %idxprom6
  %7 = load i32, i32* %j, align 4
  %idxprom8 = sext i32 %7 to i64
  %arrayidx9 = getelementptr inbounds [512 x i32], [512 x i32]* %arrayidx7, i64 0, i64 %idxprom8
  store i32 %5, i32* %arrayidx9, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body3
  %8 = load i32, i32* %j, align 4
  %inc = add nsw i32 %8, 1
  store i32 %inc, i32* %j, align 4
  br label %for.cond1

for.end:                                          ; preds = %for.cond1
  br label %for.inc10

for.inc10:                                        ; preds = %for.end
  %9 = load i32, i32* %i, align 4
  %inc11 = add nsw i32 %9, 1
  store i32 %inc11, i32* %i, align 4
  br label %for.cond

for.end12:                                        ; preds = %for.cond
  store i32 0, i32* %i, align 4
  br label %for.cond13

for.cond13:                                       ; preds = %for.inc40, %for.end12
  %10 = load i32, i32* %i, align 4
  %cmp14 = icmp slt i32 %10, 512
  br i1 %cmp14, label %for.body15, label %for.end42

for.body15:                                       ; preds = %for.cond13
  store i32 0, i32* %k, align 4
  br label %for.cond16

for.cond16:                                       ; preds = %for.inc37, %for.body15
  %11 = load i32, i32* %k, align 4
  %cmp17 = icmp slt i32 %11, 512
  br i1 %cmp17, label %for.body18, label %for.end39

for.body18:                                       ; preds = %for.cond16
  store i32 0, i32* %j, align 4

  ;a[i]
  %12 = load i32, i32* %i, align 4
  %idxprom22 = sext i32 %12 to i64
  %arrayidx23 = getelementptr inbounds [512 x [512 x i32]], [512 x [512 x i32]]* %a, i64 0, i64 %idxprom22
 
  ;a[i][k]
  %13 = load i32, i32* %k, align 4
  %idxprom24 = sext i32 %13 to i64
  %arrayidx25 = getelementptr inbounds [512 x i32], [512 x i32]* %arrayidx23, i64 0, i64 %idxprom24
  %14 = load i32, i32* %arrayidx25, align 4
 
  br label %for.cond19

for.cond19:                                       ; preds = %for.inc34, %for.body18
  %15 = load i32, i32* %j, align 4
  %cmp20 = icmp slt i32 %15, 512
  br i1 %cmp20, label %for.body21, label %for.end36

for.body21:                                       ; preds = %for.cond19

 
  %16 = load i32, i32* %k, align 4
  %idxprom26 = sext i32 %16 to i64
  %arrayidx27 = getelementptr inbounds [512 x [512 x i32]], [512 x [512 x i32]]* %b, i64 0, i64 %idxprom26
  %17 = load i32, i32* %j, align 4
  %idxprom28 = sext i32 %17 to i64
  %arrayidx29 = getelementptr inbounds [512 x i32], [512 x i32]* %arrayidx27, i64 0, i64 %idxprom28
  %18 = load i32, i32* %arrayidx29, align 4
  %mul = mul nsw i32 %14, %18
  %19 = load i32, i32* %i, align 4
  %idxprom30 = sext i32 %19 to i64
  %arrayidx31 = getelementptr inbounds [512 x [512 x i32]], [512 x [512 x i32]]* %c, i64 0, i64 %idxprom30
  %20 = load i32, i32* %j, align 4
  %idxprom32 = sext i32 %20 to i64
  %arrayidx33 = getelementptr inbounds [512 x i32], [512 x i32]* %arrayidx31, i64 0, i64 %idxprom32
  %21 = load i32, i32* %arrayidx33, align 4
  %add = add nsw i32 %21, %mul
  store i32 %add, i32* %arrayidx33, align 4
  br label %for.inc34

for.inc34:                                        ; preds = %for.body21
  %22 = load i32, i32* %j, align 4
  %inc35 = add nsw i32 %22, 1
  store i32 %inc35, i32* %j, align 4
  br label %for.cond19

for.end36:                                        ; preds = %for.cond19
  br label %for.inc37

for.inc37:                                        ; preds = %for.end36
  %23 = load i32, i32* %k, align 4
  %inc38 = add nsw i32 %23, 1
  store i32 %inc38, i32* %k, align 4
  br label %for.cond16

for.end39:                                        ; preds = %for.cond16
  br label %for.inc40

for.inc40:                                        ; preds = %for.end39
  %24 = load i32, i32* %i, align 4
  %inc41 = add nsw i32 %24, 1
  store i32 %inc41, i32* %i, align 4
  br label %for.cond13

for.end42:                                        ; preds = %for.cond13
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.0 (tags/RELEASE_800/final)"}
