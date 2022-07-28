@V12 = global <{ [40000 x i32] }> <{ [40000 x i32] zeroinitializer }>
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
define i32 @KnapSack(i32 , i32* , i32* , i32* , i32 ) {
KnapSack18:
  %v19 = alloca i32
  %v20 = alloca i32
  %v21 = alloca i32
  %v22 = alloca i32
  %v23 = alloca i32
  %v24 = alloca i32
  store i32 zeroinitializer, i32* %v24
  %v26 = alloca i32
  store i32 zeroinitializer, i32* %v26
  store i32 1, i32* %v24
  %v31 = load i32, i32* %v24
  %v32 = load i32, i32* %v19
  %bool_33 = icmp sle i32 %v31, %v32
  %bool_35 = icmp ne i1 %bool_33, false
  br i1 %bool_35, label %while_entry29, label %next_entry30
while_entry29:
  store i32 0, i32* %v26
  %v39 = load i32, i32* %v26
  %v40 = load i32, i32* %v23
  %v42 = add nsw i32 %v40, 1
  %bool_43 = icmp slt i32 %v39, %v42
  %bool_45 = icmp ne i1 %bool_43, false
  br i1 %bool_45, label %while_entry37, label %next_entry38
next_entry30:
  %v105 = load i32, i32* %v23
  store i32 %v105, i32* %v26
  %v106 = load i32, i32* %v19
  store i32 %v106, i32* %v24
  %v109 = load i32, i32* %v24
  %bool_111 = icmp sge i32 %v109, 1
  %bool_113 = icmp ne i1 %bool_111, false
  br i1 %bool_113, label %while_entry107, label %next_entry108
while_entry37:
  %v49 = load i32, i32* %v26
  %v50 = load i32, i32* %v24
  %v51 = getelementptr i32, i32* %v20, i32 0, i32 %v50
  %v52 = load i32, i32* %v51
  %bool_53 = icmp slt i32 %v49, %v52
  br i1 %bool_53, label %if_true_entry46, label %if_false_entry47
next_entry38:
  %v102 = load i32, i32* %v24
  %v104 = add nsw i32 %v102, 1
  store i32 %v104, i32* %v24
  br i1 %bool_35, label %while_entry29, label %next_entry30
if_true_entry46:
  %v54 = load i32, i32* %v24
  %v55 = load i32, i32* %v26
  %v56 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v54, i32 %v55
  %v57 = load i32, i32* %v24
  %v59 = sub nsw i32 %v57, 1
  %v60 = load i32, i32* %v26
  %v61 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v59, i32 %v60
  %v62 = load i32, i32* %v61
  store i32 %v62, i32* %v56
  br label %next_entry48
if_false_entry47:
  %v63 = alloca i32
  %v64 = load i32, i32* %v24
  %v66 = sub nsw i32 %v64, 1
  %v67 = load i32, i32* %v26
  %v68 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v66, i32 %v67
  %v69 = load i32, i32* %v68
  store i32 %v69, i32* %v63
  %v70 = alloca i32
  %v71 = load i32, i32* %v24
  %v73 = sub nsw i32 %v71, 1
  %v74 = load i32, i32* %v26
  %v75 = load i32, i32* %v24
  %v76 = getelementptr i32, i32* %v20, i32 0, i32 %v75
  %v77 = load i32, i32* %v76
  %v78 = sub nsw i32 %v74, %v77
  %v79 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v73, i32 %v78
  %v80 = load i32, i32* %v79
  %v81 = load i32, i32* %v24
  %v82 = getelementptr i32, i32* %v21, i32 0, i32 %v81
  %v83 = load i32, i32* %v82
  %v84 = add nsw i32 %v80, %v83
  store i32 %v84, i32* %v70
  %v88 = load i32, i32* %v63
  %v89 = load i32, i32* %v70
  %bool_90 = icmp sgt i32 %v88, %v89
  br i1 %bool_90, label %if_true_entry85, label %if_false_entry86
next_entry48:
  %v99 = load i32, i32* %v26
  %v101 = add nsw i32 %v99, 1
  store i32 %v101, i32* %v26
  br i1 %bool_45, label %while_entry37, label %next_entry38
if_true_entry85:
  %v91 = load i32, i32* %v24
  %v92 = load i32, i32* %v26
  %v93 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v91, i32 %v92
  %v94 = load i32, i32* %v63
  store i32 %v94, i32* %v93
  br label %next_entry87
if_false_entry86:
  %v95 = load i32, i32* %v24
  %v96 = load i32, i32* %v26
  %v97 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v95, i32 %v96
  %v98 = load i32, i32* %v70
  store i32 %v98, i32* %v97
  br label %next_entry87
next_entry87:
  br label %next_entry48
while_entry107:
  %v117 = load i32, i32* %v24
  %v118 = load i32, i32* %v26
  %v119 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v117, i32 %v118
  %v120 = load i32, i32* %v119
  %v121 = load i32, i32* %v24
  %v123 = sub nsw i32 %v121, 1
  %v124 = load i32, i32* %v26
  %v125 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v123, i32 %v124
  %v126 = load i32, i32* %v125
  %bool_127 = icmp sgt i32 %v120, %v126
  br i1 %bool_127, label %if_true_entry114, label %if_false_entry115
next_entry108:
  %v142 = load i32, i32* %v19
  %v143 = load i32, i32* %v23
  %v144 = getelementptr [200 x [200 x i32]], [200 x [200 x i32]]* @V12, i32 0, i32 %v142, i32 %v143
  %v145 = load i32, i32* %v144
  ret i32 %v145
if_true_entry114:
  %v128 = load i32, i32* %v24
  %v129 = getelementptr i32, i32* %v22, i32 0, i32 %v128
  store i32 1, i32* %v129
  %v131 = load i32, i32* %v26
  %v132 = load i32, i32* %v24
  %v133 = getelementptr i32, i32* %v20, i32 0, i32 %v132
  %v134 = load i32, i32* %v133
  %v135 = sub nsw i32 %v131, %v134
  store i32 %v135, i32* %v26
  br label %next_entry116
if_false_entry115:
  %v136 = load i32, i32* %v24
  %v137 = getelementptr i32, i32* %v22, i32 0, i32 %v136
  store i32 0, i32* %v137
  br label %next_entry116
next_entry116:
  %v139 = load i32, i32* %v24
  %v141 = sub nsw i32 %v139, 1
  store i32 %v141, i32* %v24
  br i1 %bool_113, label %while_entry107, label %next_entry108
}
define i32 @main() {
main146:
  %v147 = alloca i32
  store i32 zeroinitializer, i32* %v147
  %v156 = alloca [6 x i32]
  %v159 = getelementptr [6 x i32], [6 x i32]* %v156, i32 0, i32 0
  store i32 0, i32* %v159
  %v161 = getelementptr [6 x i32], [6 x i32]* %v156, i32 0, i32 1
  store i32 2, i32* %v161
  %v163 = getelementptr [6 x i32], [6 x i32]* %v156, i32 0, i32 2
  store i32 2, i32* %v163
  %v165 = getelementptr [6 x i32], [6 x i32]* %v156, i32 0, i32 3
  store i32 6, i32* %v165
  %v167 = getelementptr [6 x i32], [6 x i32]* %v156, i32 0, i32 4
  store i32 5, i32* %v167
  %v169 = getelementptr [6 x i32], [6 x i32]* %v156, i32 0, i32 5
  store i32 4, i32* %v169
  %v177 = alloca [6 x i32]
  %v180 = getelementptr [6 x i32], [6 x i32]* %v177, i32 0, i32 0
  store i32 0, i32* %v180
  %v182 = getelementptr [6 x i32], [6 x i32]* %v177, i32 0, i32 1
  store i32 6, i32* %v182
  %v184 = getelementptr [6 x i32], [6 x i32]* %v177, i32 0, i32 2
  store i32 3, i32* %v184
  %v186 = getelementptr [6 x i32], [6 x i32]* %v177, i32 0, i32 3
  store i32 5, i32* %v186
  %v188 = getelementptr [6 x i32], [6 x i32]* %v177, i32 0, i32 4
  store i32 4, i32* %v188
  %v190 = getelementptr [6 x i32], [6 x i32]* %v177, i32 0, i32 5
  store i32 6, i32* %v190
  %v193 = alloca [6 x i32]
  %v196 = getelementptr [6 x i32], [6 x i32]* %v193, i32 0, i32 0
  store i32 zeroinitializer, i32* %v196
  %v198 = getelementptr [6 x i32], [6 x i32]* %v193, i32 0, i32 1
  store i32 zeroinitializer, i32* %v198
  %v200 = getelementptr [6 x i32], [6 x i32]* %v193, i32 0, i32 2
  store i32 zeroinitializer, i32* %v200
  %v202 = getelementptr [6 x i32], [6 x i32]* %v193, i32 0, i32 3
  store i32 zeroinitializer, i32* %v202
  %v204 = getelementptr [6 x i32], [6 x i32]* %v193, i32 0, i32 4
  store i32 zeroinitializer, i32* %v204
  %v206 = getelementptr [6 x i32], [6 x i32]* %v193, i32 0, i32 5
  store i32 zeroinitializer, i32* %v206
  %v207 = alloca i32
  store i32 5, i32* %v207
  %v209 = alloca i32
  store i32 10, i32* %v209
  %v211 = load i32, i32* %v207
  %v212 = load [6 x i32], [6 x i32]* %v156
  %v213 = load [6 x i32], [6 x i32]* %v177
  %v214 = load [6 x i32], [6 x i32]* %v193
  %v215 = load i32, i32* %v209
  %v216 = call i32 @KnapSack(i32 %v211, [6 x i32] %v212, [6 x i32] %v213, [6 x i32] %v214, i32 %v215)
  store i32 %v216, i32* %v147
  %v217 = load i32, i32* %v147
  call void @putint(i32 %v217)
  ret i32 0
}

