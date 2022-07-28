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
define i32 @bubblesort(i32* ) {
bubblesort11:
  %v12 = alloca i32
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  store i32 0, i32* %v13
  %v20 = load i32, i32* %v13
  %v21 = load i32, i32* @n9
  %v23 = sub nsw i32 %v21, 1
  %bool_24 = icmp slt i32 %v20, %v23
  %bool_26 = icmp ne i1 %bool_24, false
  br i1 %bool_26, label %while_entry18, label %next_entry19
while_entry18:
  store i32 0, i32* %v15
  %v30 = load i32, i32* %v15
  %v31 = load i32, i32* @n9
  %v32 = load i32, i32* %v13
  %v33 = sub nsw i32 %v31, %v32
  %v35 = sub nsw i32 %v33, 1
  %bool_36 = icmp slt i32 %v30, %v35
  %bool_38 = icmp ne i1 %bool_36, false
  br i1 %bool_38, label %while_entry28, label %next_entry29
next_entry19:
  ret i32 0
while_entry28:
  %v42 = load i32, i32* %v15
  %v43 = getelementptr i32, i32* %v12, i32 0, i32 %v42
  %v44 = load i32, i32* %v43
  %v45 = load i32, i32* %v15
  %v47 = add nsw i32 %v45, 1
  %v48 = getelementptr i32, i32* %v12, i32 0, i32 %v47
  %v49 = load i32, i32* %v48
  %bool_50 = icmp sgt i32 %v44, %v49
  br i1 %bool_50, label %if_true_entry39, label %next_entry41
next_entry29:
  %v71 = load i32, i32* %v13
  %v73 = add nsw i32 %v71, 1
  store i32 %v73, i32* %v13
  br i1 %bool_26, label %while_entry18, label %next_entry19
if_true_entry39:
  %v51 = alloca i32
  store i32 zeroinitializer, i32* %v51
  %v53 = load i32, i32* %v15
  %v55 = add nsw i32 %v53, 1
  %v56 = getelementptr i32, i32* %v12, i32 0, i32 %v55
  %v57 = load i32, i32* %v56
  store i32 %v57, i32* %v51
  %v58 = load i32, i32* %v15
  %v60 = add nsw i32 %v58, 1
  %v61 = getelementptr i32, i32* %v12, i32 0, i32 %v60
  %v62 = load i32, i32* %v15
  %v63 = getelementptr i32, i32* %v12, i32 0, i32 %v62
  %v64 = load i32, i32* %v63
  store i32 %v64, i32* %v61
  %v65 = load i32, i32* %v15
  %v66 = getelementptr i32, i32* %v12, i32 0, i32 %v65
  %v67 = load i32, i32* %v51
  store i32 %v67, i32* %v66
  br label %next_entry41
next_entry41:
  %v68 = load i32, i32* %v15
  %v70 = add nsw i32 %v68, 1
  store i32 %v70, i32* %v15
  br i1 %bool_38, label %while_entry28, label %next_entry29
}
define i32 @main() {
main75:
  store i32 10, i32* @n9
  %v79 = alloca [10 x i32]
  %v82 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 0
  store i32 zeroinitializer, i32* %v82
  %v84 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 1
  store i32 zeroinitializer, i32* %v84
  %v86 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 2
  store i32 zeroinitializer, i32* %v86
  %v88 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 3
  store i32 zeroinitializer, i32* %v88
  %v90 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 4
  store i32 zeroinitializer, i32* %v90
  %v92 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 5
  store i32 zeroinitializer, i32* %v92
  %v94 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 6
  store i32 zeroinitializer, i32* %v94
  %v96 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 7
  store i32 zeroinitializer, i32* %v96
  %v98 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 8
  store i32 zeroinitializer, i32* %v98
  %v100 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 9
  store i32 zeroinitializer, i32* %v100
  %v103 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 0
  store i32 4, i32* %v103
  %v107 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 1
  store i32 3, i32* %v107
  %v111 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 2
  store i32 9, i32* %v111
  %v115 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 3
  store i32 2, i32* %v115
  %v119 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 4
  store i32 0, i32* %v119
  %v123 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 5
  store i32 1, i32* %v123
  %v127 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 6
  store i32 6, i32* %v127
  %v131 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 7
  store i32 5, i32* %v131
  %v135 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 8
  store i32 7, i32* %v135
  %v139 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 9
  store i32 8, i32* %v139
  %v141 = alloca i32
  store i32 zeroinitializer, i32* %v141
  %v143 = load [10 x i32], [10 x i32]* %v79
  %v144 = call i32 @bubblesort([10 x i32] %v143)
  store i32 %v144, i32* %v141
  %v147 = load i32, i32* %v141
  %v148 = load i32, i32* @n9
  %bool_149 = icmp slt i32 %v147, %v148
  %bool_151 = icmp ne i1 %bool_149, false
  br i1 %bool_151, label %while_entry145, label %next_entry146
while_entry145:
  %v152 = alloca i32
  store i32 zeroinitializer, i32* %v152
  %v154 = load i32, i32* %v141
  %v155 = getelementptr [10 x i32], [10 x i32]* %v79, i32 0, i32 %v154
  %v156 = load i32, i32* %v155
  store i32 %v156, i32* %v152
  %v157 = load i32, i32* %v152
  call void @putint(i32 %v157)
  store i32 10, i32* %v152
  %v160 = load i32, i32* %v152
  call void @putch(i32 %v160)
  %v162 = load i32, i32* %v141
  %v164 = add nsw i32 %v162, 1
  store i32 %v164, i32* %v141
  br i1 %bool_151, label %while_entry145, label %next_entry146
next_entry146:
  ret i32 0
}

