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
define i32 @QuickSort(i32* , i32 , i32 ) {
QuickSort13:
  %v14 = alloca i32
  %v15 = alloca i32
  %v16 = alloca i32
  %v20 = load i32, i32* %v15
  %v21 = load i32, i32* %v16
  %bool_22 = icmp slt i32 %v20, %v21
  br i1 %bool_22, label %if_true_entry17, label %next_entry19
if_true_entry17:
  %v23 = alloca i32
  store i32 zeroinitializer, i32* %v23
  %v25 = load i32, i32* %v15
  store i32 %v25, i32* %v23
  %v26 = alloca i32
  store i32 zeroinitializer, i32* %v26
  %v28 = load i32, i32* %v16
  store i32 %v28, i32* %v26
  %v29 = alloca i32
  store i32 zeroinitializer, i32* %v29
  %v31 = load i32, i32* %v15
  %v32 = getelementptr i32, i32* %v14, i32 0, i32 %v31
  %v33 = load i32, i32* %v32
  store i32 %v33, i32* %v29
  %v36 = load i32, i32* %v23
  %v37 = load i32, i32* %v26
  %bool_38 = icmp slt i32 %v36, %v37
  %bool_40 = icmp ne i1 %bool_38, false
  br i1 %bool_40, label %while_entry34, label %next_entry35
next_entry19:
  ret i32 0
while_entry34:
  %v45 = load i32, i32* %v23
  %v46 = load i32, i32* %v26
  %bool_47 = icmp slt i32 %v45, %v46
  %bool_49 = icmp ne i1 %bool_47, zeroinitializer
  br i1 %bool_49, label %l43, label %r44
next_entry35:
  %v103 = load i32, i32* %v23
  %v104 = getelementptr i32, i32* %v14, i32 0, i32 %v103
  %v105 = load i32, i32* %v29
  store i32 %v105, i32* %v104
  %v106 = alloca i32
  store i32 zeroinitializer, i32* %v106
  %v108 = load i32, i32* %v23
  %v110 = sub nsw i32 %v108, 1
  store i32 %v110, i32* %v106
  %v111 = load i32, i32* %v14
  %v112 = load i32, i32* %v15
  %v113 = load i32, i32* %v106
  %v114 = call i32 @QuickSort(i32 %v111, i32 %v112, i32 %v113)
  store i32 %v114, i32* %v106
  %v115 = load i32, i32* %v23
  %v117 = add nsw i32 %v115, 1
  store i32 %v117, i32* %v106
  %v118 = load i32, i32* %v14
  %v119 = load i32, i32* %v106
  %v120 = load i32, i32* %v16
  %v121 = call i32 @QuickSort(i32 %v118, i32 %v119, i32 %v120)
  store i32 %v121, i32* %v106
  br label %next_entry19
while_entry41:
next_entry42:
  %v62 = load i32, i32* %v23
  %v63 = load i32, i32* %v26
  %bool_64 = icmp slt i32 %v62, %v63
  br i1 %bool_64, label %if_true_entry59, label %next_entry61
l43:
  %v50 = load i32, i32* %v26
  %v51 = getelementptr i32, i32* %v14, i32 0, i32 %v50
  %v52 = load i32, i32* %v51
  %v53 = load i32, i32* %v29
  %v55 = sub nsw i32 %v53, 1
  %bool_56 = icmp sgt i32 %v52, %v55
  %bool_58 = icmp ne i1 %bool_56, zeroinitializer
  br i1 %bool_58, label %while_entry41, label %r44
r44:
  br label %next_entry35
if_true_entry59:
  %v65 = load i32, i32* %v23
  %v66 = getelementptr i32, i32* %v14, i32 0, i32 %v65
  %v67 = load i32, i32* %v26
  %v68 = getelementptr i32, i32* %v14, i32 0, i32 %v67
  %v69 = load i32, i32* %v68
  store i32 %v69, i32* %v66
  %v70 = load i32, i32* %v23
  %v72 = add nsw i32 %v70, 1
  store i32 %v72, i32* %v23
  br label %next_entry61
next_entry61:
  %v77 = load i32, i32* %v23
  %v78 = load i32, i32* %v26
  %bool_79 = icmp slt i32 %v77, %v78
  %bool_81 = icmp ne i1 %bool_79, zeroinitializer
  br i1 %bool_81, label %l75, label %r76
while_entry73:
next_entry74:
  %v92 = load i32, i32* %v23
  %v93 = load i32, i32* %v26
  %bool_94 = icmp slt i32 %v92, %v93
  br i1 %bool_94, label %if_true_entry89, label %next_entry91
l75:
  %v82 = load i32, i32* %v23
  %v83 = getelementptr i32, i32* %v14, i32 0, i32 %v82
  %v84 = load i32, i32* %v83
  %v85 = load i32, i32* %v29
  %bool_86 = icmp slt i32 %v84, %v85
  %bool_88 = icmp ne i1 %bool_86, zeroinitializer
  br i1 %bool_88, label %while_entry73, label %r76
r76:
  br label %next_entry35
if_true_entry89:
  %v95 = load i32, i32* %v26
  %v96 = getelementptr i32, i32* %v14, i32 0, i32 %v95
  %v97 = load i32, i32* %v23
  %v98 = getelementptr i32, i32* %v14, i32 0, i32 %v97
  %v99 = load i32, i32* %v98
  store i32 %v99, i32* %v96
  %v100 = load i32, i32* %v26
  %v102 = sub nsw i32 %v100, 1
  store i32 %v102, i32* %v26
  br label %next_entry91
next_entry91:
  br i1 %bool_40, label %while_entry34, label %next_entry35
}
define i32 @main() {
main123:
  store i32 10, i32* @n9
  %v127 = alloca [10 x i32]
  %v130 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 0
  store i32 zeroinitializer, i32* %v130
  %v132 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 1
  store i32 zeroinitializer, i32* %v132
  %v134 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 2
  store i32 zeroinitializer, i32* %v134
  %v136 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 3
  store i32 zeroinitializer, i32* %v136
  %v138 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 4
  store i32 zeroinitializer, i32* %v138
  %v140 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 5
  store i32 zeroinitializer, i32* %v140
  %v142 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 6
  store i32 zeroinitializer, i32* %v142
  %v144 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 7
  store i32 zeroinitializer, i32* %v144
  %v146 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 8
  store i32 zeroinitializer, i32* %v146
  %v148 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 9
  store i32 zeroinitializer, i32* %v148
  %v151 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 0
  store i32 4, i32* %v151
  %v155 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 1
  store i32 3, i32* %v155
  %v159 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 2
  store i32 9, i32* %v159
  %v163 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 3
  store i32 2, i32* %v163
  %v167 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 4
  store i32 0, i32* %v167
  %v171 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 5
  store i32 1, i32* %v171
  %v175 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 6
  store i32 6, i32* %v175
  %v179 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 7
  store i32 5, i32* %v179
  %v183 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 8
  store i32 7, i32* %v183
  %v187 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 9
  store i32 8, i32* %v187
  %v189 = alloca i32
  store i32 zeroinitializer, i32* %v189
  store i32 0, i32* %v189
  %v192 = alloca i32
  store i32 zeroinitializer, i32* %v192
  store i32 9, i32* %v192
  %v195 = load [10 x i32], [10 x i32]* %v127
  %v196 = load i32, i32* %v189
  %v197 = load i32, i32* %v192
  %v198 = call i32 @QuickSort([10 x i32] %v195, i32 %v196, i32 %v197)
  store i32 %v198, i32* %v189
  %v201 = load i32, i32* %v189
  %v202 = load i32, i32* @n9
  %bool_203 = icmp slt i32 %v201, %v202
  %bool_205 = icmp ne i1 %bool_203, false
  br i1 %bool_205, label %while_entry199, label %next_entry200
while_entry199:
  %v206 = alloca i32
  store i32 zeroinitializer, i32* %v206
  %v208 = load i32, i32* %v189
  %v209 = getelementptr [10 x i32], [10 x i32]* %v127, i32 0, i32 %v208
  %v210 = load i32, i32* %v209
  store i32 %v210, i32* %v206
  %v211 = load i32, i32* %v206
  call void @putint(i32 %v211)
  store i32 10, i32* %v206
  %v214 = load i32, i32* %v206
  call void @putch(i32 %v214)
  %v216 = load i32, i32* %v189
  %v218 = add nsw i32 %v216, 1
  store i32 %v218, i32* %v189
  br i1 %bool_205, label %while_entry199, label %next_entry200
next_entry200:
  ret i32 0
}

