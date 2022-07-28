define void @putint(i32 ) {
putint1:
  ret void
}
define void @putch(i32 ) {
putch3:
  ret void
}
define i32 @getint() {
getint4:
  ret i32 0
}
define i32 @getch() {
getch6:
  ret i32 0
}
define i32 @climbStairs(i32 ) {
climbStairs9:
  %v10 = alloca i32
  %v14 = load i32, i32* %v10
  %bool_16 = icmp slt i32 %v14, 4
  br i1 %bool_16, label %if_true_entry11, label %next_entry13
if_true_entry11:
  %v17 = load i32, i32* %v10
  ret i32 %v17
next_entry13:
  %v20 = alloca [10 x i32]
  %v23 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 0
  store i32 zeroinitializer, i32* %v23
  %v25 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 1
  store i32 zeroinitializer, i32* %v25
  %v27 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 2
  store i32 zeroinitializer, i32* %v27
  %v29 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 3
  store i32 zeroinitializer, i32* %v29
  %v31 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 4
  store i32 zeroinitializer, i32* %v31
  %v33 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 5
  store i32 zeroinitializer, i32* %v33
  %v35 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 6
  store i32 zeroinitializer, i32* %v35
  %v37 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 7
  store i32 zeroinitializer, i32* %v37
  %v39 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 8
  store i32 zeroinitializer, i32* %v39
  %v41 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 9
  store i32 zeroinitializer, i32* %v41
  %v44 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 0
  store i32 0, i32* %v44
  %v48 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 1
  store i32 1, i32* %v48
  %v52 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 2
  store i32 2, i32* %v52
  %v54 = alloca i32
  store i32 zeroinitializer, i32* %v54
  store i32 3, i32* %v54
  %v59 = load i32, i32* %v54
  %v60 = load i32, i32* %v10
  %v62 = add nsw i32 %v60, 1
  %bool_63 = icmp slt i32 %v59, %v62
  %bool_65 = icmp ne i1 %bool_63, false
  br i1 %bool_65, label %while_entry57, label %next_entry58
while_entry57:
  %v66 = load i32, i32* %v54
  %v67 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 %v66
  %v68 = load i32, i32* %v54
  %v70 = sub nsw i32 %v68, 1
  %v71 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 %v70
  %v72 = load i32, i32* %v71
  %v73 = load i32, i32* %v54
  %v75 = sub nsw i32 %v73, 2
  %v76 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 %v75
  %v77 = load i32, i32* %v76
  %v78 = add nsw i32 %v72, %v77
  store i32 %v78, i32* %v67
  %v79 = load i32, i32* %v54
  %v81 = add nsw i32 %v79, 1
  store i32 %v81, i32* %v54
  br i1 %bool_65, label %while_entry57, label %next_entry58
next_entry58:
  %v82 = load i32, i32* %v10
  %v83 = getelementptr [10 x i32], [10 x i32]* %v20, i32 0, i32 %v82
  %v84 = load i32, i32* %v83
  ret i32 %v84
}
define i32 @main() {
main85:
  %v86 = alloca i32
  store i32 zeroinitializer, i32* %v86
  %v88 = alloca i32
  store i32 zeroinitializer, i32* %v88
  store i32 5, i32* %v88
  %v91 = load i32, i32* %v88
  %v92 = call i32 @climbStairs(i32 %v91)
  store i32 %v92, i32* %v86
  %v93 = load i32, i32* %v86
  ret i32 %v93
}

