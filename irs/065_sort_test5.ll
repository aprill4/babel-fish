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
define i32 @swap(i32* , i32 , i32 ) {
swap13:
  %v14 = alloca i32
  %v15 = alloca i32
  %v16 = alloca i32
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  %v19 = load i32, i32* %v15
  %v20 = getelementptr i32, i32* %v14, i32 0, i32 %v19
  %v21 = load i32, i32* %v20
  store i32 %v21, i32* %v17
  %v22 = load i32, i32* %v15
  %v23 = getelementptr i32, i32* %v14, i32 0, i32 %v22
  %v24 = load i32, i32* %v16
  %v25 = getelementptr i32, i32* %v14, i32 0, i32 %v24
  %v26 = load i32, i32* %v25
  store i32 %v26, i32* %v23
  %v27 = load i32, i32* %v16
  %v28 = getelementptr i32, i32* %v14, i32 0, i32 %v27
  %v29 = load i32, i32* %v17
  store i32 %v29, i32* %v28
  ret i32 0
}
define i32 @heap_ajust(i32* , i32 , i32 ) {
heap_ajust34:
  %v35 = alloca i32
  %v36 = alloca i32
  %v37 = alloca i32
  %v38 = alloca i32
  store i32 zeroinitializer, i32* %v38
  %v40 = load i32, i32* %v36
  store i32 %v40, i32* %v38
  %v41 = alloca i32
  store i32 zeroinitializer, i32* %v41
  %v43 = load i32, i32* %v38
  %v45 = mul i32 %v43, 2
  %v47 = add nsw i32 %v45, 1
  store i32 %v47, i32* %v41
  %v50 = load i32, i32* %v41
  %v51 = load i32, i32* %v37
  %v53 = add nsw i32 %v51, 1
  %bool_54 = icmp slt i32 %v50, %v53
  %bool_56 = icmp ne i1 %bool_54, false
  br i1 %bool_56, label %while_entry48, label %next_entry49
while_entry48:
  %v62 = load i32, i32* %v41
  %v63 = load i32, i32* %v37
  %bool_64 = icmp slt i32 %v62, %v63
  %bool_66 = icmp ne i1 %bool_64, zeroinitializer
  br i1 %bool_66, label %l60, label %r61
next_entry49:
  ret i32 0
if_true_entry57:
  %v78 = load i32, i32* %v41
  %v80 = add nsw i32 %v78, 1
  store i32 %v80, i32* %v41
  br label %next_entry59
next_entry59:
  %v84 = load i32, i32* %v38
  %v85 = getelementptr i32, i32* %v35, i32 0, i32 %v84
  %v86 = load i32, i32* %v85
  %v87 = load i32, i32* %v41
  %v88 = getelementptr i32, i32* %v35, i32 0, i32 %v87
  %v89 = load i32, i32* %v88
  %bool_90 = icmp sgt i32 %v86, %v89
  br i1 %bool_90, label %if_true_entry81, label %if_false_entry82
l60:
  %v67 = load i32, i32* %v41
  %v68 = getelementptr i32, i32* %v35, i32 0, i32 %v67
  %v69 = load i32, i32* %v68
  %v70 = load i32, i32* %v41
  %v72 = add nsw i32 %v70, 1
  %v73 = getelementptr i32, i32* %v35, i32 0, i32 %v72
  %v74 = load i32, i32* %v73
  %bool_75 = icmp slt i32 %v69, %v74
  %bool_77 = icmp ne i1 %bool_75, zeroinitializer
  br i1 %bool_77, label %if_true_entry57, label %r61
r61:
  br label %next_entry49
if_true_entry81:
  ret i32 0
if_false_entry82:
  %v92 = load i32, i32* %v35
  %v93 = load i32, i32* %v38
  %v94 = load i32, i32* %v41
  %v95 = call i32 @swap(i32 %v92, i32 %v93, i32 %v94)
  store i32 %v95, i32* %v38
  %v96 = load i32, i32* %v41
  store i32 %v96, i32* %v38
  %v97 = load i32, i32* %v38
  %v99 = mul i32 %v97, 2
  %v101 = add nsw i32 %v99, 1
  store i32 %v101, i32* %v41
  br label %next_entry83
next_entry83:
  br i1 %bool_56, label %while_entry48, label %next_entry49
}
define i32 @heap_sort(i32* , i32 ) {
heap_sort105:
  %v106 = alloca i32
  %v107 = alloca i32
  %v108 = alloca i32
  store i32 zeroinitializer, i32* %v108
  %v110 = alloca i32
  store i32 zeroinitializer, i32* %v110
  %v112 = load i32, i32* %v107
  %v114 = sdiv i32 %v112, 2
  %v116 = sub nsw i32 %v114, 1
  store i32 %v116, i32* %v108
  %v119 = load i32, i32* %v108
  %v122 = sub nsw i32 0, 1
  %bool_123 = icmp sgt i32 %v119, %v122
  %bool_125 = icmp ne i1 %bool_123, false
  br i1 %bool_125, label %while_entry117, label %next_entry118
while_entry117:
  %v126 = load i32, i32* %v107
  %v128 = sub nsw i32 %v126, 1
  store i32 %v128, i32* %v110
  %v129 = load i32, i32* %v106
  %v130 = load i32, i32* %v108
  %v131 = load i32, i32* %v110
  %v132 = call i32 @heap_ajust(i32 %v129, i32 %v130, i32 %v131)
  store i32 %v132, i32* %v110
  %v133 = load i32, i32* %v108
  %v135 = sub nsw i32 %v133, 1
  store i32 %v135, i32* %v108
  br i1 %bool_125, label %while_entry117, label %next_entry118
next_entry118:
  %v136 = load i32, i32* %v107
  %v138 = sub nsw i32 %v136, 1
  store i32 %v138, i32* %v108
  %v141 = load i32, i32* %v108
  %bool_143 = icmp sgt i32 %v141, 0
  %bool_145 = icmp ne i1 %bool_143, false
  br i1 %bool_145, label %while_entry139, label %next_entry140
while_entry139:
  %v146 = alloca i32
  store i32 zeroinitializer, i32* %v146
  store i32 0, i32* %v146
  %v149 = load i32, i32* %v106
  %v150 = load i32, i32* %v146
  %v151 = load i32, i32* %v108
  %v152 = call i32 @swap(i32 %v149, i32 %v150, i32 %v151)
  store i32 %v152, i32* %v110
  %v153 = load i32, i32* %v108
  %v155 = sub nsw i32 %v153, 1
  store i32 %v155, i32* %v110
  %v156 = load i32, i32* %v106
  %v157 = load i32, i32* %v146
  %v158 = load i32, i32* %v110
  %v159 = call i32 @heap_ajust(i32 %v156, i32 %v157, i32 %v158)
  store i32 %v159, i32* %v110
  %v160 = load i32, i32* %v108
  %v162 = sub nsw i32 %v160, 1
  store i32 %v162, i32* %v108
  br i1 %bool_145, label %while_entry139, label %next_entry140
next_entry140:
  ret i32 0
}
define i32 @main() {
main164:
  store i32 10, i32* @n9
  %v168 = alloca [10 x i32]
  %v171 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 0
  store i32 zeroinitializer, i32* %v171
  %v173 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 1
  store i32 zeroinitializer, i32* %v173
  %v175 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 2
  store i32 zeroinitializer, i32* %v175
  %v177 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 3
  store i32 zeroinitializer, i32* %v177
  %v179 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 4
  store i32 zeroinitializer, i32* %v179
  %v181 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 5
  store i32 zeroinitializer, i32* %v181
  %v183 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 6
  store i32 zeroinitializer, i32* %v183
  %v185 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 7
  store i32 zeroinitializer, i32* %v185
  %v187 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 8
  store i32 zeroinitializer, i32* %v187
  %v189 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 9
  store i32 zeroinitializer, i32* %v189
  %v192 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 0
  store i32 4, i32* %v192
  %v196 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 1
  store i32 3, i32* %v196
  %v200 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 2
  store i32 9, i32* %v200
  %v204 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 3
  store i32 2, i32* %v204
  %v208 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 4
  store i32 0, i32* %v208
  %v212 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 5
  store i32 1, i32* %v212
  %v216 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 6
  store i32 6, i32* %v216
  %v220 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 7
  store i32 5, i32* %v220
  %v224 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 8
  store i32 7, i32* %v224
  %v228 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 9
  store i32 8, i32* %v228
  %v230 = alloca i32
  store i32 zeroinitializer, i32* %v230
  store i32 0, i32* %v230
  %v233 = load [10 x i32], [10 x i32]* %v168
  %v234 = load i32, i32* @n9
  %v235 = call i32 @heap_sort([10 x i32] %v233, i32 %v234)
  store i32 %v235, i32* %v230
  %v238 = load i32, i32* %v230
  %v239 = load i32, i32* @n9
  %bool_240 = icmp slt i32 %v238, %v239
  %bool_242 = icmp ne i1 %bool_240, false
  br i1 %bool_242, label %while_entry236, label %next_entry237
while_entry236:
  %v243 = alloca i32
  store i32 zeroinitializer, i32* %v243
  %v245 = load i32, i32* %v230
  %v246 = getelementptr [10 x i32], [10 x i32]* %v168, i32 0, i32 %v245
  %v247 = load i32, i32* %v246
  store i32 %v247, i32* %v243
  %v248 = load i32, i32* %v243
  call void @putint(i32 %v248)
  store i32 10, i32* %v243
  %v251 = load i32, i32* %v243
  call void @putch(i32 %v251)
  %v253 = load i32, i32* %v230
  %v255 = add nsw i32 %v253, 1
  store i32 %v255, i32* %v230
  br i1 %bool_242, label %while_entry236, label %next_entry237
next_entry237:
  ret i32 0
}

