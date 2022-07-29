@n9 = global i32 zeroinitializer
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
define i32 @insertsort(i32* ) {
insertsort11:
  %v12 = alloca i32
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  store i32 1, i32* %v13
  %v18 = load i32, i32* %v13
  %v19 = load i32, i32* @n9
  %bool_20 = icmp slt i32 %v18, %v19
  %bool_22 = icmp ne i1 %bool_20, false
  br i1 %bool_22, label %while_entry16, label %next_entry17
while_entry16:
  %v23 = alloca i32
  store i32 zeroinitializer, i32* %v23
  %v25 = load i32, i32* %v13
  %v26 = getelementptr i32, i32* %v12, i32 0, i32 %v25
  %v27 = load i32, i32* %v26
  store i32 %v27, i32* %v23
  %v28 = alloca i32
  store i32 zeroinitializer, i32* %v28
  %v30 = load i32, i32* %v13
  %v32 = sub nsw i32 %v30, 1
  store i32 %v32, i32* %v28
  %v37 = load i32, i32* %v28
  %v40 = sub nsw i32 0, 1
  %bool_41 = icmp sgt i32 %v37, %v40
  %bool_43 = icmp ne i1 %bool_41, zeroinitializer
  br i1 %bool_43, label %l35, label %r36
next_entry17:
  ret i32 0
while_entry33:
next_entry34:
  %v51 = load i32, i32* %v28
  %v53 = add nsw i32 %v51, 1
  %v54 = getelementptr i32, i32* %v12, i32 0, i32 %v53
  %v55 = load i32, i32* %v23
  store i32 %v55, i32* %v54
  %v56 = load i32, i32* %v13
  %v58 = add nsw i32 %v56, 1
  store i32 %v58, i32* %v13
  br i1 %bool_22, label %while_entry16, label %next_entry17
l35:
  %v44 = load i32, i32* %v23
  %v45 = load i32, i32* %v28
  %v46 = getelementptr i32, i32* %v12, i32 0, i32 %v45
  %v47 = load i32, i32* %v46
  %bool_48 = icmp slt i32 %v44, %v47
  %bool_50 = icmp ne i1 %bool_48, zeroinitializer
  br i1 %bool_50, label %while_entry33, label %r36
r36:
  br label %next_entry17
}
define i32 @main() {
main60:
  store i32 10, i32* @n9
  %v64 = alloca [10 x i32]
  %v67 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 0
  store i32 zeroinitializer, i32* %v67
  %v69 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 1
  store i32 zeroinitializer, i32* %v69
  %v71 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 2
  store i32 zeroinitializer, i32* %v71
  %v73 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 3
  store i32 zeroinitializer, i32* %v73
  %v75 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 4
  store i32 zeroinitializer, i32* %v75
  %v77 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 5
  store i32 zeroinitializer, i32* %v77
  %v79 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 6
  store i32 zeroinitializer, i32* %v79
  %v81 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 7
  store i32 zeroinitializer, i32* %v81
  %v83 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 8
  store i32 zeroinitializer, i32* %v83
  %v85 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 9
  store i32 zeroinitializer, i32* %v85
  %v88 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 0
  store i32 4, i32* %v88
  %v92 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 1
  store i32 3, i32* %v92
  %v96 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 2
  store i32 9, i32* %v96
  %v100 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 3
  store i32 2, i32* %v100
  %v104 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 4
  store i32 0, i32* %v104
  %v108 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 5
  store i32 1, i32* %v108
  %v112 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 6
  store i32 6, i32* %v112
  %v116 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 7
  store i32 5, i32* %v116
  %v120 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 8
  store i32 7, i32* %v120
  %v124 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 9
  store i32 8, i32* %v124
  %v126 = alloca i32
  store i32 zeroinitializer, i32* %v126
  %v128 = load [10 x i32], [10 x i32]* %v64
  %v129 = call i32 @insertsort([10 x i32] %v128)
  store i32 %v129, i32* %v126
  %v132 = load i32, i32* %v126
  %v133 = load i32, i32* @n9
  %bool_134 = icmp slt i32 %v132, %v133
  %bool_136 = icmp ne i1 %bool_134, false
  br i1 %bool_136, label %while_entry130, label %next_entry131
while_entry130:
  %v137 = alloca i32
  store i32 zeroinitializer, i32* %v137
  %v139 = load i32, i32* %v126
  %v140 = getelementptr [10 x i32], [10 x i32]* %v64, i32 0, i32 %v139
  %v141 = load i32, i32* %v140
  store i32 %v141, i32* %v137
  %v142 = load i32, i32* %v137
  call void @putint(i32 %v142)
  store i32 10, i32* %v137
  %v145 = load i32, i32* %v137
  call void @putch(i32 %v145)
  %v147 = load i32, i32* %v126
  %v149 = add nsw i32 %v147, 1
  store i32 %v149, i32* %v126
  br i1 %bool_136, label %while_entry130, label %next_entry131
next_entry131:
  ret i32 0
}

