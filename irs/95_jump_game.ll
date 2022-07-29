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
define i32 @canJump(i32* , i32 ) {
canJump10:
  %v11 = alloca i32
  %v12 = alloca i32
  %v16 = load i32, i32* %v12
  %bool_18 = icmp eq i32 %v16, 1
  br i1 %bool_18, label %if_true_entry13, label %next_entry15
if_true_entry13:
  ret i32 1
next_entry15:
  %v25 = getelementptr i32, i32* %v11, i32 0, i32 0
  %v26 = load i32, i32* %v25
  %v27 = load i32, i32* %v12
  %v29 = sub nsw i32 %v27, 2
  %bool_30 = icmp sgt i32 %v26, %v29
  br i1 %bool_30, label %if_true_entry20, label %next_entry22
if_true_entry20:
  ret i32 1
next_entry22:
  %v34 = alloca [10 x i32]
  %v37 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 0
  store i32 zeroinitializer, i32* %v37
  %v39 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 1
  store i32 zeroinitializer, i32* %v39
  %v41 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 2
  store i32 zeroinitializer, i32* %v41
  %v43 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 3
  store i32 zeroinitializer, i32* %v43
  %v45 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 4
  store i32 zeroinitializer, i32* %v45
  %v47 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 5
  store i32 zeroinitializer, i32* %v47
  %v49 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 6
  store i32 zeroinitializer, i32* %v49
  %v51 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 7
  store i32 zeroinitializer, i32* %v51
  %v53 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 8
  store i32 zeroinitializer, i32* %v53
  %v55 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 9
  store i32 zeroinitializer, i32* %v55
  %v56 = alloca i32
  store i32 zeroinitializer, i32* %v56
  store i32 0, i32* %v56
  %v61 = load i32, i32* %v56
  %v62 = load i32, i32* %v12
  %v64 = sub nsw i32 %v62, 1
  %bool_65 = icmp slt i32 %v61, %v64
  %bool_67 = icmp ne i1 %bool_65, false
  br i1 %bool_67, label %while_entry59, label %next_entry60
while_entry59:
  %v68 = load i32, i32* %v56
  %v69 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 %v68
  store i32 0, i32* %v69
  %v71 = load i32, i32* %v56
  %v73 = add nsw i32 %v71, 1
  store i32 %v73, i32* %v56
  br i1 %bool_67, label %while_entry59, label %next_entry60
next_entry60:
  %v74 = load i32, i32* %v12
  %v76 = sub nsw i32 %v74, 1
  %v77 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 %v76
  store i32 1, i32* %v77
  %v79 = load i32, i32* %v12
  %v81 = sub nsw i32 %v79, 2
  store i32 %v81, i32* %v56
  %v84 = load i32, i32* %v56
  %v87 = sub nsw i32 0, 1
  %bool_88 = icmp sgt i32 %v84, %v87
  %bool_90 = icmp ne i1 %bool_88, false
  br i1 %bool_90, label %while_entry82, label %next_entry83
while_entry82:
  %v91 = alloca i32
  store i32 zeroinitializer, i32* %v91
  %v96 = load i32, i32* %v56
  %v97 = getelementptr i32, i32* %v11, i32 0, i32 %v96
  %v98 = load i32, i32* %v97
  %v99 = load i32, i32* %v12
  %v101 = sub nsw i32 %v99, 1
  %v102 = load i32, i32* %v56
  %v103 = sub nsw i32 %v101, %v102
  %bool_104 = icmp slt i32 %v98, %v103
  br i1 %bool_104, label %if_true_entry93, label %if_false_entry94
next_entry83:
  %v143 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 0
  %v144 = load i32, i32* %v143
  ret i32 %v144
if_true_entry93:
  %v105 = load i32, i32* %v56
  %v106 = getelementptr i32, i32* %v11, i32 0, i32 %v105
  %v107 = load i32, i32* %v106
  store i32 %v107, i32* %v91
  br label %next_entry95
if_false_entry94:
  %v108 = load i32, i32* %v12
  %v110 = sub nsw i32 %v108, 1
  %v111 = load i32, i32* %v56
  %v112 = sub nsw i32 %v110, %v111
  store i32 %v112, i32* %v91
  br label %next_entry95
next_entry95:
  %v115 = load i32, i32* %v91
  %v118 = sub nsw i32 0, 1
  %bool_119 = icmp sgt i32 %v115, %v118
  %bool_121 = icmp ne i1 %bool_119, false
  br i1 %bool_121, label %while_entry113, label %next_entry114
while_entry113:
  %v125 = load i32, i32* %v56
  %v126 = load i32, i32* %v91
  %v127 = add nsw i32 %v125, %v126
  %v128 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 %v127
  %v129 = load i32, i32* %v128
  %bool_131 = icmp ne i32 %v129, 0
  br i1 %bool_131, label %if_true_entry122, label %next_entry124
next_entry114:
  %v138 = load i32, i32* %v56
  %v140 = sub nsw i32 %v138, 1
  store i32 %v140, i32* %v56
  br i1 %bool_90, label %while_entry82, label %next_entry83
if_true_entry122:
  %v132 = load i32, i32* %v56
  %v133 = getelementptr [10 x i32], [10 x i32]* %v34, i32 0, i32 %v132
  store i32 1, i32* %v133
  br label %next_entry124
next_entry124:
  %v135 = load i32, i32* %v91
  %v137 = sub nsw i32 %v135, 1
  store i32 %v137, i32* %v91
  br i1 %bool_121, label %while_entry113, label %next_entry114
}
define i32 @main() {
main145:
  %v146 = alloca i32
  store i32 zeroinitializer, i32* %v146
  %v150 = alloca [10 x i32]
  %v153 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 0
  store i32 zeroinitializer, i32* %v153
  %v155 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 1
  store i32 zeroinitializer, i32* %v155
  %v157 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 2
  store i32 zeroinitializer, i32* %v157
  %v159 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 3
  store i32 zeroinitializer, i32* %v159
  %v161 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 4
  store i32 zeroinitializer, i32* %v161
  %v163 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 5
  store i32 zeroinitializer, i32* %v163
  %v165 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 6
  store i32 zeroinitializer, i32* %v165
  %v167 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 7
  store i32 zeroinitializer, i32* %v167
  %v169 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 8
  store i32 zeroinitializer, i32* %v169
  %v171 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 9
  store i32 zeroinitializer, i32* %v171
  %v174 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 0
  store i32 3, i32* %v174
  %v178 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 1
  store i32 3, i32* %v178
  %v182 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 2
  store i32 9, i32* %v182
  %v186 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 3
  store i32 0, i32* %v186
  %v190 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 4
  store i32 0, i32* %v190
  %v194 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 5
  store i32 1, i32* %v194
  %v198 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 6
  store i32 1, i32* %v198
  %v202 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 7
  store i32 5, i32* %v202
  %v206 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 8
  store i32 7, i32* %v206
  %v210 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 9
  store i32 8, i32* %v210
  store i32 10, i32* %v146
  %v213 = load [10 x i32], [10 x i32]* %v150
  %v214 = load i32, i32* %v146
  %v215 = call i32 @canJump([10 x i32] %v213, i32 %v214)
  store i32 %v215, i32* %v146
  %v216 = load i32, i32* %v146
  ret i32 %v216
}

