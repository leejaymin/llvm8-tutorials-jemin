; ModuleID = 'test.bc'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [14 x i8] c"Hello world!\0A\00", align 1
@.str.1 = private unnamed_addr constant [15 x i8] c"%d + %d = %d \0A\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  %a = alloca [1024 x [1024 x i32]], align 16
  %b = alloca [1024 x [1024 x i32]], align 16
  %c = alloca [1024 x [1024 x i32]], align 16
  store i32 0, i32* %retval, align 4
  store i32 1, i32* %x, align 4
  store i32 2, i32* %y, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0))
  %0 = load i32, i32* %x, align 4
  %1 = load i32, i32* %y, align 4
  %2 = load i32, i32* %x, align 4
  %3 = load i32, i32* %y, align 4
  %call1 = call i32 @add(i32 %2, i32 %3)
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.1, i32 0, i32 0), i32 %0, i32 %1, i32 %call1)
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc12, %entry
  %4 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %4, 1024
  br i1 %cmp, label %for.body, label %for.end14

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4
  br label %for.cond3

for.cond3:                                        ; preds = %for.inc, %for.body
  %5 = load i32, i32* %j, align 4
  %cmp4 = icmp slt i32 %5, 1024
  br i1 %cmp4, label %for.body5, label %for.end

for.body5:                                        ; preds = %for.cond3
  %6 = load i32, i32* %i, align 4
  %7 = load i32, i32* %i, align 4
  %idxprom = sext i32 %7 to i64
  %arrayidx = getelementptr inbounds [1024 x [1024 x i32]], [1024 x [1024 x i32]]* %a, i64 0, i64 %idxprom
  %8 = load i32, i32* %j, align 4
  %idxprom6 = sext i32 %8 to i64
  %arrayidx7 = getelementptr inbounds [1024 x i32], [1024 x i32]* %arrayidx, i64 0, i64 %idxprom6
  store i32 %6, i32* %arrayidx7, align 4
  %9 = load i32, i32* %j, align 4
  %10 = load i32, i32* %i, align 4
  %idxprom8 = sext i32 %10 to i64
  %arrayidx9 = getelementptr inbounds [1024 x [1024 x i32]], [1024 x [1024 x i32]]* %b, i64 0, i64 %idxprom8
  %11 = load i32, i32* %j, align 4
  %idxprom10 = sext i32 %11 to i64
  %arrayidx11 = getelementptr inbounds [1024 x i32], [1024 x i32]* %arrayidx9, i64 0, i64 %idxprom10
  store i32 %9, i32* %arrayidx11, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body5
  %12 = load i32, i32* %j, align 4
  %inc = add nsw i32 %12, 1
  store i32 %inc, i32* %j, align 4
  br label %for.cond3

for.end:                                          ; preds = %for.cond3
  br label %for.inc12

for.inc12:                                        ; preds = %for.end
  %13 = load i32, i32* %i, align 4
  %inc13 = add nsw i32 %13, 1
  store i32 %inc13, i32* %i, align 4
  br label %for.cond

for.end14:                                        ; preds = %for.cond
  store i32 0, i32* %i, align 4
  br label %for.cond15

for.cond15:                                       ; preds = %for.inc42, %for.end14
  %14 = load i32, i32* %i, align 4
  %cmp16 = icmp slt i32 %14, 1024
  br i1 %cmp16, label %for.body17, label %for.end44

for.body17:                                       ; preds = %for.cond15
  store i32 0, i32* %k, align 4
  br label %for.cond18

for.cond18:                                       ; preds = %for.inc39, %for.body17
  %15 = load i32, i32* %k, align 4
  %cmp19 = icmp slt i32 %15, 1024
  br i1 %cmp19, label %for.body20, label %for.end41

for.body20:                                       ; preds = %for.cond18
  store i32 0, i32* %j, align 4
  br label %for.cond21

for.cond21:                                       ; preds = %for.inc36, %for.body20
  %16 = load i32, i32* %j, align 4
  %cmp22 = icmp slt i32 %16, 1024
  br i1 %cmp22, label %for.body23, label %for.end38

for.body23:                                       ; preds = %for.cond21
  %17 = load i32, i32* %i, align 4
  %idxprom24 = sext i32 %17 to i64
  %arrayidx25 = getelementptr inbounds [1024 x [1024 x i32]], [1024 x [1024 x i32]]* %a, i64 0, i64 %idxprom24
  %18 = load i32, i32* %k, align 4
  %idxprom26 = sext i32 %18 to i64
  %arrayidx27 = getelementptr inbounds [1024 x i32], [1024 x i32]* %arrayidx25, i64 0, i64 %idxprom26
  %19 = load i32, i32* %arrayidx27, align 4
  %20 = load i32, i32* %k, align 4
  %idxprom28 = sext i32 %20 to i64
  %arrayidx29 = getelementptr inbounds [1024 x [1024 x i32]], [1024 x [1024 x i32]]* %b, i64 0, i64 %idxprom28
  %21 = load i32, i32* %j, align 4
  %idxprom30 = sext i32 %21 to i64
  %arrayidx31 = getelementptr inbounds [1024 x i32], [1024 x i32]* %arrayidx29, i64 0, i64 %idxprom30
  %22 = load i32, i32* %arrayidx31, align 4
  %mul = mul nsw i32 %19, %22
  %23 = load i32, i32* %i, align 4
  %idxprom32 = sext i32 %23 to i64
  %arrayidx33 = getelementptr inbounds [1024 x [1024 x i32]], [1024 x [1024 x i32]]* %c, i64 0, i64 %idxprom32
  %24 = load i32, i32* %j, align 4
  %idxprom34 = sext i32 %24 to i64
  %arrayidx35 = getelementptr inbounds [1024 x i32], [1024 x i32]* %arrayidx33, i64 0, i64 %idxprom34
  %25 = load i32, i32* %arrayidx35, align 4
  %add = add nsw i32 %25, %mul
  store i32 %add, i32* %arrayidx35, align 4
  br label %for.inc36

for.inc36:                                        ; preds = %for.body23
  %26 = load i32, i32* %j, align 4
  %inc37 = add nsw i32 %26, 1
  store i32 %inc37, i32* %j, align 4
  br label %for.cond21

for.end38:                                        ; preds = %for.cond21
  br label %for.inc39

for.inc39:                                        ; preds = %for.end38
  %27 = load i32, i32* %k, align 4
  %inc40 = add nsw i32 %27, 1
  store i32 %inc40, i32* %k, align 4
  br label %for.cond18

for.end41:                                        ; preds = %for.cond18
  br label %for.inc42

for.inc42:                                        ; preds = %for.end41
  %28 = load i32, i32* %i, align 4
  %inc43 = add nsw i32 %28, 1
  store i32 %inc43, i32* %i, align 4
  br label %for.cond15

for.end44:                                        ; preds = %for.cond15
  %29 = load i32, i32* %i, align 4
  %idxprom45 = sext i32 %29 to i64
  %arrayidx46 = getelementptr inbounds [1024 x [1024 x i32]], [1024 x [1024 x i32]]* %c, i64 0, i64 %idxprom45
  %30 = load i32, i32* %j, align 4
  %idxprom47 = sext i32 %30 to i64
  %arrayidx48 = getelementptr inbounds [1024 x i32], [1024 x i32]* %arrayidx46, i64 0, i64 %idxprom47
  %31 = load i32, i32* %arrayidx48, align 4
  %call49 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i32 0, i32 0), i32 %31)
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @add(i32 %x, i32 %y) #0 {
entry:
  %x.addr = alloca i32, align 4
  %y.addr = alloca i32, align 4
  store i32 %x, i32* %x.addr, align 4
  store i32 %y, i32* %y.addr, align 4
  %0 = load i32, i32* %x.addr, align 4
  %1 = load i32, i32* %y.addr, align 4
  %add = add nsw i32 %0, %1
  ret i32 %add
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.0 (tags/RELEASE_800/final)"}
