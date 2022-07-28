@N9 = global i32 zeroinitializer
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
define i32 @insert(i32* , i32 ) {
insert12:
  %v13 = alloca i32
  %v14 = alloca i32
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  store i32 0, i32* %v15
  %v24 = load i32, i32* %v14
  %v25 = load i32, i32* %v15
  %v26 = getelementptr i32, i32* %v13, i32 0, i32 %v25
  %v27 = load i32, i32* %v26
  %bool_28 = icmp sgt i32 %v24, %v27
  %bool_30 = icmp ne i1 %bool_28, zeroinitializer
  br i1 %bool_30, label %l22, label %r23
while_entry20:
next_entry21:
  %v36 = load i32, i32* @N9
  store i32 %v36, i32* %v17
  %v39 = load i32, i32* %v17
  %v40 = load i32, i32* %v15
  %bool_41 = icmp sgt i32 %v39, %v40
  %bool_43 = icmp ne i1 %bool_41, false
  br i1 %bool_43, label %while_entry37, label %next_entry38
l22:
  %v31 = load i32, i32* %v15
  %v32 = load i32, i32* @N9
  %bool_33 = icmp slt i32 %v31, %v32
  %bool_35 = icmp ne i1 %bool_33, zeroinitializer
  br i1 %bool_35, label %while_entry20, label %r23
r23:
  br label %next_entry21
while_entry37:
  %v44 = load i32, i32* %v17
  %v45 = getelementptr i32, i32* %v13, i32 0, i32 %v44
  %v46 = load i32, i32* %v17
  %v48 = sub nsw i32 %v46, 1
  %v49 = getelementptr i32, i32* %v13, i32 0, i32 %v48
  %v50 = load i32, i32* %v49
  store i32 %v50, i32* %v45
  %v51 = load i32, i32* %v15
  %v52 = getelementptr i32, i32* %v13, i32 0, i32 %v51
  %v53 = load i32, i32* %v14
  store i32 %v53, i32* %v52
  %v54 = load i32, i32* %v17
  %v56 = sub nsw i32 %v54, 1
  store i32 %v56, i32* %v17
  br i1 %bool_43, label %while_entry37, label %next_entry38
next_entry38:
  ret i32 0
}
define i32 @main() {
main58:
  store i32 10, i32* @N9
  %v62 = alloca [11 x i32]
  %v65 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 0
  store i32 zeroinitializer, i32* %v65
  %v67 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 1
  store i32 zeroinitializer, i32* %v67
  %v69 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 2
  store i32 zeroinitializer, i32* %v69
  %v71 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 3
  store i32 zeroinitializer, i32* %v71
  %v73 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 4
  store i32 zeroinitializer, i32* %v73
  %v75 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 5
  store i32 zeroinitializer, i32* %v75
  %v77 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 6
  store i32 zeroinitializer, i32* %v77
  %v79 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 7
  store i32 zeroinitializer, i32* %v79
  %v81 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 8
  store i32 zeroinitializer, i32* %v81
  %v83 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 9
  store i32 zeroinitializer, i32* %v83
  %v85 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 10
  store i32 zeroinitializer, i32* %v85
  %v88 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 0
  store i32 1, i32* %v88
  %v92 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 1
  store i32 3, i32* %v92
  %v96 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 2
  store i32 4, i32* %v96
  %v100 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 3
  store i32 7, i32* %v100
  %v104 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 4
  store i32 8, i32* %v104
  %v108 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 5
  store i32 11, i32* %v108
  %v112 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 6
  store i32 13, i32* %v112
  %v116 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 7
  store i32 18, i32* %v116
  %v120 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 8
  store i32 56, i32* %v120
  %v124 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 9
  store i32 78, i32* %v124
  %v126 = alloca i32
  store i32 zeroinitializer, i32* %v126
  %v128 = alloca i32
  store i32 zeroinitializer, i32* %v128
  store i32 0, i32* %v128
  %v131 = call i32 @getint()
  store i32 %v131, i32* %v126
  %v132 = load [11 x i32], [11 x i32]* %v62
  %v133 = load i32, i32* %v126
  %v134 = call i32 @insert([11 x i32] %v132, i32 %v133)
  store i32 %v134, i32* %v126
  %v137 = load i32, i32* %v128
  %v138 = load i32, i32* @N9
  %bool_139 = icmp slt i32 %v137, %v138
  %bool_141 = icmp ne i1 %bool_139, false
  br i1 %bool_141, label %while_entry135, label %next_entry136
while_entry135:
  %v142 = load i32, i32* %v128
  %v143 = getelementptr [11 x i32], [11 x i32]* %v62, i32 0, i32 %v142
  %v144 = load i32, i32* %v143
  store i32 %v144, i32* %v126
  %v145 = load i32, i32* %v126
  call void @putint(i32 %v145)
  store i32 10, i32* %v126
  %v148 = load i32, i32* %v126
  call void @putch(i32 %v148)
  %v150 = load i32, i32* %v128
  %v152 = add nsw i32 %v150, 1
  store i32 %v152, i32* %v128
  br i1 %bool_141, label %while_entry135, label %next_entry136
next_entry136:
  ret i32 0
}

