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
define i32 @maxSubArray(i32* , i32 ) {
maxSubArray10:
  %v11 = alloca i32
  %v12 = alloca i32
  %v16 = load i32, i32* %v12
  %bool_18 = icmp eq i32 %v16, 0
  br i1 %bool_18, label %if_true_entry13, label %next_entry15
if_true_entry13:
  ret i32 0
next_entry15:
  %v23 = load i32, i32* %v12
  %bool_25 = icmp eq i32 %v23, 1
  br i1 %bool_25, label %if_true_entry20, label %next_entry22
if_true_entry20:
  %v28 = getelementptr i32, i32* %v11, i32 0, i32 0
  %v29 = load i32, i32* %v28
  ret i32 %v29
next_entry22:
  %v30 = alloca i32
  store i32 zeroinitializer, i32* %v30
  %v34 = getelementptr i32, i32* %v11, i32 0, i32 0
  %v35 = load i32, i32* %v34
  store i32 %v35, i32* %v30
  %v36 = alloca i32
  store i32 zeroinitializer, i32* %v36
  %v38 = load i32, i32* %v30
  store i32 %v38, i32* %v36
  %v39 = alloca i32
  store i32 zeroinitializer, i32* %v39
  store i32 1, i32* %v39
  %v44 = load i32, i32* %v39
  %v45 = load i32, i32* %v12
  %bool_46 = icmp slt i32 %v44, %v45
  %bool_48 = icmp ne i1 %bool_46, false
  br i1 %bool_48, label %while_entry42, label %next_entry43
while_entry42:
  %v52 = load i32, i32* %v30
  %bool_54 = icmp slt i32 %v52, 0
  br i1 %bool_54, label %if_true_entry49, label %next_entry51
next_entry43:
  %v71 = load i32, i32* %v36
  ret i32 %v71
if_true_entry49:
  store i32 0, i32* %v30
  br label %next_entry51
next_entry51:
  %v56 = load i32, i32* %v30
  %v57 = load i32, i32* %v39
  %v58 = getelementptr i32, i32* %v11, i32 0, i32 %v57
  %v59 = load i32, i32* %v58
  %v60 = add nsw i32 %v56, %v59
  store i32 %v60, i32* %v30
  %v64 = load i32, i32* %v36
  %v65 = load i32, i32* %v30
  %bool_66 = icmp slt i32 %v64, %v65
  br i1 %bool_66, label %if_true_entry61, label %next_entry63
if_true_entry61:
  %v67 = load i32, i32* %v30
  store i32 %v67, i32* %v36
  br label %next_entry63
next_entry63:
  %v68 = load i32, i32* %v39
  %v70 = add nsw i32 %v68, 1
  store i32 %v70, i32* %v39
  br i1 %bool_48, label %while_entry42, label %next_entry43
}
define i32 @main() {
main72:
  %v73 = alloca i32
  store i32 zeroinitializer, i32* %v73
  %v77 = alloca [10 x i32]
  %v80 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 0
  store i32 zeroinitializer, i32* %v80
  %v82 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 1
  store i32 zeroinitializer, i32* %v82
  %v84 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 2
  store i32 zeroinitializer, i32* %v84
  %v86 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 3
  store i32 zeroinitializer, i32* %v86
  %v88 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 4
  store i32 zeroinitializer, i32* %v88
  %v90 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 5
  store i32 zeroinitializer, i32* %v90
  %v92 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 6
  store i32 zeroinitializer, i32* %v92
  %v94 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 7
  store i32 zeroinitializer, i32* %v94
  %v96 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 8
  store i32 zeroinitializer, i32* %v96
  %v98 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 9
  store i32 zeroinitializer, i32* %v98
  %v101 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 0
  %v104 = sub nsw i32 0, 4
  store i32 %v104, i32* %v101
  %v107 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 1
  store i32 3, i32* %v107
  %v111 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 2
  store i32 9, i32* %v111
  %v115 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 3
  %v118 = sub nsw i32 0, 2
  store i32 %v118, i32* %v115
  %v121 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 4
  store i32 0, i32* %v121
  %v125 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 5
  store i32 1, i32* %v125
  %v129 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 6
  %v132 = sub nsw i32 0, 6
  store i32 %v132, i32* %v129
  %v135 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 7
  store i32 5, i32* %v135
  %v139 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 8
  store i32 7, i32* %v139
  %v143 = getelementptr [10 x i32], [10 x i32]* %v77, i32 0, i32 9
  store i32 8, i32* %v143
  store i32 10, i32* %v73
  %v146 = load [10 x i32], [10 x i32]* %v77
  %v147 = load i32, i32* %v73
  %v148 = call i32 @maxSubArray([10 x i32] %v146, i32 %v147)
  store i32 %v148, i32* %v73
  %v149 = load i32, i32* %v73
  ret i32 %v149
}

