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
define i32 @select_sort(i32* , i32 ) {
select_sort12:
  %v13 = alloca i32
  %v14 = alloca i32
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  %v19 = alloca i32
  store i32 zeroinitializer, i32* %v19
  store i32 0, i32* %v15
  %v24 = load i32, i32* %v15
  %v25 = load i32, i32* %v14
  %v27 = sub nsw i32 %v25, 1
  %bool_28 = icmp slt i32 %v24, %v27
  %bool_30 = icmp ne i1 %bool_28, false
  br i1 %bool_30, label %while_entry22, label %next_entry23
while_entry22:
  %v31 = load i32, i32* %v15
  store i32 %v31, i32* %v19
  %v32 = load i32, i32* %v15
  %v34 = add nsw i32 %v32, 1
  store i32 %v34, i32* %v17
  %v37 = load i32, i32* %v17
  %v38 = load i32, i32* %v14
  %bool_39 = icmp slt i32 %v37, %v38
  %bool_41 = icmp ne i1 %bool_39, false
  br i1 %bool_41, label %while_entry35, label %next_entry36
next_entry23:
  ret i32 0
while_entry35:
  %v45 = load i32, i32* %v19
  %v46 = getelementptr i32, i32* %v13, i32 0, i32 %v45
  %v47 = load i32, i32* %v46
  %v48 = load i32, i32* %v17
  %v49 = getelementptr i32, i32* %v13, i32 0, i32 %v48
  %v50 = load i32, i32* %v49
  %bool_51 = icmp sgt i32 %v47, %v50
  br i1 %bool_51, label %if_true_entry42, label %next_entry44
next_entry36:
  %v59 = load i32, i32* %v19
  %v60 = load i32, i32* %v15
  %bool_61 = icmp ne i32 %v59, %v60
  br i1 %bool_61, label %if_true_entry56, label %next_entry58
if_true_entry42:
  %v52 = load i32, i32* %v17
  store i32 %v52, i32* %v19
  br label %next_entry44
next_entry44:
  %v53 = load i32, i32* %v17
  %v55 = add nsw i32 %v53, 1
  store i32 %v55, i32* %v17
  br i1 %bool_41, label %while_entry35, label %next_entry36
if_true_entry56:
  %v62 = alloca i32
  store i32 zeroinitializer, i32* %v62
  %v64 = load i32, i32* %v19
  %v65 = getelementptr i32, i32* %v13, i32 0, i32 %v64
  %v66 = load i32, i32* %v65
  store i32 %v66, i32* %v62
  %v67 = load i32, i32* %v19
  %v68 = getelementptr i32, i32* %v13, i32 0, i32 %v67
  %v69 = load i32, i32* %v15
  %v70 = getelementptr i32, i32* %v13, i32 0, i32 %v69
  %v71 = load i32, i32* %v70
  store i32 %v71, i32* %v68
  %v72 = load i32, i32* %v15
  %v73 = getelementptr i32, i32* %v13, i32 0, i32 %v72
  %v74 = load i32, i32* %v62
  store i32 %v74, i32* %v73
  br label %next_entry58
next_entry58:
  %v75 = load i32, i32* %v15
  %v77 = add nsw i32 %v75, 1
  store i32 %v77, i32* %v15
  br i1 %bool_30, label %while_entry22, label %next_entry23
}
define i32 @main() {
main79:
  store i32 10, i32* @n9
  %v83 = alloca [10 x i32]
  %v86 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 0
  store i32 zeroinitializer, i32* %v86
  %v88 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 1
  store i32 zeroinitializer, i32* %v88
  %v90 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 2
  store i32 zeroinitializer, i32* %v90
  %v92 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 3
  store i32 zeroinitializer, i32* %v92
  %v94 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 4
  store i32 zeroinitializer, i32* %v94
  %v96 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 5
  store i32 zeroinitializer, i32* %v96
  %v98 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 6
  store i32 zeroinitializer, i32* %v98
  %v100 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 7
  store i32 zeroinitializer, i32* %v100
  %v102 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 8
  store i32 zeroinitializer, i32* %v102
  %v104 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 9
  store i32 zeroinitializer, i32* %v104
  %v107 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 0
  store i32 4, i32* %v107
  %v111 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 1
  store i32 3, i32* %v111
  %v115 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 2
  store i32 9, i32* %v115
  %v119 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 3
  store i32 2, i32* %v119
  %v123 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 4
  store i32 0, i32* %v123
  %v127 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 5
  store i32 1, i32* %v127
  %v131 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 6
  store i32 6, i32* %v131
  %v135 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 7
  store i32 5, i32* %v135
  %v139 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 8
  store i32 7, i32* %v139
  %v143 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 9
  store i32 8, i32* %v143
  %v145 = alloca i32
  store i32 zeroinitializer, i32* %v145
  store i32 0, i32* %v145
  %v148 = load [10 x i32], [10 x i32]* %v83
  %v149 = load i32, i32* @n9
  %v150 = call i32 @select_sort([10 x i32] %v148, i32 %v149)
  store i32 %v150, i32* %v145
  %v153 = load i32, i32* %v145
  %v154 = load i32, i32* @n9
  %bool_155 = icmp slt i32 %v153, %v154
  %bool_157 = icmp ne i1 %bool_155, false
  br i1 %bool_157, label %while_entry151, label %next_entry152
while_entry151:
  %v158 = alloca i32
  store i32 zeroinitializer, i32* %v158
  %v160 = load i32, i32* %v145
  %v161 = getelementptr [10 x i32], [10 x i32]* %v83, i32 0, i32 %v160
  %v162 = load i32, i32* %v161
  store i32 %v162, i32* %v158
  %v163 = load i32, i32* %v158
  call void @putint(i32 %v163)
  store i32 10, i32* %v158
  %v166 = load i32, i32* %v158
  call void @putch(i32 %v166)
  %v168 = load i32, i32* %v145
  %v170 = add nsw i32 %v168, 1
  store i32 %v170, i32* %v145
  br i1 %bool_157, label %while_entry151, label %next_entry152
next_entry152:
  ret i32 0
}

