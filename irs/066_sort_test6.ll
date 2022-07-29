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
define i32 @counting_sort(i32* , i32* , i32 ) {
counting_sort13:
  %v14 = alloca i32
  %v15 = alloca i32
  %v16 = alloca i32
  %v19 = alloca [10 x i32]
  %v22 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 0
  store i32 zeroinitializer, i32* %v22
  %v24 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 1
  store i32 zeroinitializer, i32* %v24
  %v26 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 2
  store i32 zeroinitializer, i32* %v26
  %v28 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 3
  store i32 zeroinitializer, i32* %v28
  %v30 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 4
  store i32 zeroinitializer, i32* %v30
  %v32 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 5
  store i32 zeroinitializer, i32* %v32
  %v34 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 6
  store i32 zeroinitializer, i32* %v34
  %v36 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 7
  store i32 zeroinitializer, i32* %v36
  %v38 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 8
  store i32 zeroinitializer, i32* %v38
  %v40 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 9
  store i32 zeroinitializer, i32* %v40
  %v41 = alloca i32
  store i32 zeroinitializer, i32* %v41
  %v43 = alloca i32
  store i32 zeroinitializer, i32* %v43
  %v45 = alloca i32
  store i32 zeroinitializer, i32* %v45
  store i32 0, i32* %v45
  store i32 0, i32* %v41
  store i32 0, i32* %v43
  %v52 = load i32, i32* %v45
  %bool_54 = icmp slt i32 %v52, 10
  %bool_56 = icmp ne i1 %bool_54, false
  br i1 %bool_56, label %while_entry50, label %next_entry51
while_entry50:
  %v57 = load i32, i32* %v45
  %v58 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v57
  store i32 0, i32* %v58
  %v60 = load i32, i32* %v45
  %v62 = add nsw i32 %v60, 1
  store i32 %v62, i32* %v45
  br i1 %bool_56, label %while_entry50, label %next_entry51
next_entry51:
  %v65 = load i32, i32* %v41
  %v66 = load i32, i32* %v16
  %bool_67 = icmp slt i32 %v65, %v66
  %bool_69 = icmp ne i1 %bool_67, false
  br i1 %bool_69, label %while_entry63, label %next_entry64
while_entry63:
  %v70 = load i32, i32* %v41
  %v71 = getelementptr i32, i32* %v14, i32 0, i32 %v70
  %v72 = load i32, i32* %v71
  %v73 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v72
  %v74 = load i32, i32* %v41
  %v75 = getelementptr i32, i32* %v14, i32 0, i32 %v74
  %v76 = load i32, i32* %v75
  %v77 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v76
  %v78 = load i32, i32* %v77
  %v80 = add nsw i32 %v78, 1
  store i32 %v80, i32* %v73
  %v81 = load i32, i32* %v41
  %v83 = add nsw i32 %v81, 1
  store i32 %v83, i32* %v41
  br i1 %bool_69, label %while_entry63, label %next_entry64
next_entry64:
  store i32 1, i32* %v45
  %v87 = load i32, i32* %v45
  %bool_89 = icmp slt i32 %v87, 10
  %bool_91 = icmp ne i1 %bool_89, false
  br i1 %bool_91, label %while_entry85, label %next_entry86
while_entry85:
  %v92 = load i32, i32* %v45
  %v93 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v92
  %v94 = load i32, i32* %v45
  %v95 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v94
  %v96 = load i32, i32* %v95
  %v97 = load i32, i32* %v45
  %v99 = sub nsw i32 %v97, 1
  %v100 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v99
  %v101 = load i32, i32* %v100
  %v102 = add nsw i32 %v96, %v101
  store i32 %v102, i32* %v93
  %v103 = load i32, i32* %v45
  %v105 = add nsw i32 %v103, 1
  store i32 %v105, i32* %v45
  br i1 %bool_91, label %while_entry85, label %next_entry86
next_entry86:
  %v106 = load i32, i32* %v16
  store i32 %v106, i32* %v43
  %v109 = load i32, i32* %v43
  %bool_111 = icmp sgt i32 %v109, 0
  %bool_113 = icmp ne i1 %bool_111, false
  br i1 %bool_113, label %while_entry107, label %next_entry108
while_entry107:
  %v114 = load i32, i32* %v43
  %v116 = sub nsw i32 %v114, 1
  %v117 = getelementptr i32, i32* %v14, i32 0, i32 %v116
  %v118 = load i32, i32* %v117
  %v119 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v118
  %v120 = load i32, i32* %v43
  %v122 = sub nsw i32 %v120, 1
  %v123 = getelementptr i32, i32* %v14, i32 0, i32 %v122
  %v124 = load i32, i32* %v123
  %v125 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v124
  %v126 = load i32, i32* %v125
  %v128 = sub nsw i32 %v126, 1
  store i32 %v128, i32* %v119
  %v129 = load i32, i32* %v43
  %v131 = sub nsw i32 %v129, 1
  %v132 = getelementptr i32, i32* %v14, i32 0, i32 %v131
  %v133 = load i32, i32* %v132
  %v134 = getelementptr [10 x i32], [10 x i32]* %v19, i32 0, i32 %v133
  %v135 = load i32, i32* %v134
  %v136 = getelementptr i32, i32* %v15, i32 0, i32 %v135
  %v137 = load i32, i32* %v43
  %v139 = sub nsw i32 %v137, 1
  %v140 = getelementptr i32, i32* %v14, i32 0, i32 %v139
  %v141 = load i32, i32* %v140
  store i32 %v141, i32* %v136
  %v142 = load i32, i32* %v43
  %v144 = sub nsw i32 %v142, 1
  store i32 %v144, i32* %v43
  br i1 %bool_113, label %while_entry107, label %next_entry108
next_entry108:
  ret i32 0
}
define i32 @main() {
main146:
  store i32 10, i32* @n9
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
  store i32 4, i32* %v174
  %v178 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 1
  store i32 3, i32* %v178
  %v182 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 2
  store i32 9, i32* %v182
  %v186 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 3
  store i32 2, i32* %v186
  %v190 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 4
  store i32 0, i32* %v190
  %v194 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 5
  store i32 1, i32* %v194
  %v198 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 6
  store i32 6, i32* %v198
  %v202 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 7
  store i32 5, i32* %v202
  %v206 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 8
  store i32 7, i32* %v206
  %v210 = getelementptr [10 x i32], [10 x i32]* %v150, i32 0, i32 9
  store i32 8, i32* %v210
  %v212 = alloca i32
  store i32 zeroinitializer, i32* %v212
  store i32 0, i32* %v212
  %v217 = alloca [10 x i32]
  %v220 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 0
  store i32 zeroinitializer, i32* %v220
  %v222 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 1
  store i32 zeroinitializer, i32* %v222
  %v224 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 2
  store i32 zeroinitializer, i32* %v224
  %v226 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 3
  store i32 zeroinitializer, i32* %v226
  %v228 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 4
  store i32 zeroinitializer, i32* %v228
  %v230 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 5
  store i32 zeroinitializer, i32* %v230
  %v232 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 6
  store i32 zeroinitializer, i32* %v232
  %v234 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 7
  store i32 zeroinitializer, i32* %v234
  %v236 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 8
  store i32 zeroinitializer, i32* %v236
  %v238 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 9
  store i32 zeroinitializer, i32* %v238
  %v239 = load [10 x i32], [10 x i32]* %v150
  %v240 = load [10 x i32], [10 x i32]* %v217
  %v241 = load i32, i32* @n9
  %v242 = call i32 @counting_sort([10 x i32] %v239, [10 x i32] %v240, i32 %v241)
  store i32 %v242, i32* %v212
  %v245 = load i32, i32* %v212
  %v246 = load i32, i32* @n9
  %bool_247 = icmp slt i32 %v245, %v246
  %bool_249 = icmp ne i1 %bool_247, false
  br i1 %bool_249, label %while_entry243, label %next_entry244
while_entry243:
  %v250 = alloca i32
  store i32 zeroinitializer, i32* %v250
  %v252 = load i32, i32* %v212
  %v253 = getelementptr [10 x i32], [10 x i32]* %v217, i32 0, i32 %v252
  %v254 = load i32, i32* %v253
  store i32 %v254, i32* %v250
  %v255 = load i32, i32* %v250
  call void @putint(i32 %v255)
  store i32 10, i32* %v250
  %v258 = load i32, i32* %v250
  call void @putch(i32 %v258)
  %v260 = load i32, i32* %v212
  %v262 = add nsw i32 %v260, 1
  store i32 %v262, i32* %v212
  br i1 %bool_249, label %while_entry243, label %next_entry244
next_entry244:
  ret i32 0
}

