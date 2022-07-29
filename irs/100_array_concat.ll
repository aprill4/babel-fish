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
define i32 @concat(i32* , i32* , i32* ) {
concat11:
  %v12 = alloca i32
  %v13 = alloca i32
  %v14 = alloca i32
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  store i32 0, i32* %v15
  %v20 = load i32, i32* %v15
  %bool_22 = icmp slt i32 %v20, 3
  %bool_24 = icmp ne i1 %bool_22, false
  br i1 %bool_24, label %while_entry18, label %next_entry19
while_entry18:
  %v25 = load i32, i32* %v15
  %v26 = getelementptr i32, i32* %v14, i32 0, i32 %v25
  %v27 = load i32, i32* %v15
  %v28 = getelementptr i32, i32* %v12, i32 0, i32 %v27
  %v29 = load i32, i32* %v28
  store i32 %v29, i32* %v26
  %v30 = load i32, i32* %v15
  %v32 = add nsw i32 %v30, 1
  store i32 %v32, i32* %v15
  br i1 %bool_24, label %while_entry18, label %next_entry19
next_entry19:
  %v33 = alloca i32
  store i32 zeroinitializer, i32* %v33
  store i32 0, i32* %v33
  %v38 = load i32, i32* %v33
  %bool_40 = icmp slt i32 %v38, 3
  %bool_42 = icmp ne i1 %bool_40, false
  br i1 %bool_42, label %while_entry36, label %next_entry37
while_entry36:
  %v43 = load i32, i32* %v15
  %v44 = getelementptr i32, i32* %v14, i32 0, i32 %v43
  %v45 = load i32, i32* %v33
  %v46 = getelementptr i32, i32* %v13, i32 0, i32 %v45
  %v47 = load i32, i32* %v46
  store i32 %v47, i32* %v44
  %v48 = load i32, i32* %v15
  %v50 = add nsw i32 %v48, 1
  store i32 %v50, i32* %v15
  %v51 = load i32, i32* %v33
  %v53 = add nsw i32 %v51, 1
  store i32 %v53, i32* %v33
  br i1 %bool_42, label %while_entry36, label %next_entry37
next_entry37:
  ret i32 0
}
define i32 @main() {
main55:
  %v58 = alloca [3 x i32]
  %v61 = getelementptr [3 x i32], [3 x i32]* %v58, i32 0, i32 0
  store i32 zeroinitializer, i32* %v61
  %v63 = getelementptr [3 x i32], [3 x i32]* %v58, i32 0, i32 1
  store i32 zeroinitializer, i32* %v63
  %v65 = getelementptr [3 x i32], [3 x i32]* %v58, i32 0, i32 2
  store i32 zeroinitializer, i32* %v65
  %v68 = alloca [3 x i32]
  %v71 = getelementptr [3 x i32], [3 x i32]* %v68, i32 0, i32 0
  store i32 zeroinitializer, i32* %v71
  %v73 = getelementptr [3 x i32], [3 x i32]* %v68, i32 0, i32 1
  store i32 zeroinitializer, i32* %v73
  %v75 = getelementptr [3 x i32], [3 x i32]* %v68, i32 0, i32 2
  store i32 zeroinitializer, i32* %v75
  %v78 = alloca [3 x i32]
  %v81 = getelementptr [3 x i32], [3 x i32]* %v78, i32 0, i32 0
  store i32 zeroinitializer, i32* %v81
  %v83 = getelementptr [3 x i32], [3 x i32]* %v78, i32 0, i32 1
  store i32 zeroinitializer, i32* %v83
  %v85 = getelementptr [3 x i32], [3 x i32]* %v78, i32 0, i32 2
  store i32 zeroinitializer, i32* %v85
  %v88 = alloca [3 x i32]
  %v91 = getelementptr [3 x i32], [3 x i32]* %v88, i32 0, i32 0
  store i32 zeroinitializer, i32* %v91
  %v93 = getelementptr [3 x i32], [3 x i32]* %v88, i32 0, i32 1
  store i32 zeroinitializer, i32* %v93
  %v95 = getelementptr [3 x i32], [3 x i32]* %v88, i32 0, i32 2
  store i32 zeroinitializer, i32* %v95
  %v98 = alloca [3 x i32]
  %v101 = getelementptr [3 x i32], [3 x i32]* %v98, i32 0, i32 0
  store i32 zeroinitializer, i32* %v101
  %v103 = getelementptr [3 x i32], [3 x i32]* %v98, i32 0, i32 1
  store i32 zeroinitializer, i32* %v103
  %v105 = getelementptr [3 x i32], [3 x i32]* %v98, i32 0, i32 2
  store i32 zeroinitializer, i32* %v105
  %v108 = alloca [3 x i32]
  %v111 = getelementptr [3 x i32], [3 x i32]* %v108, i32 0, i32 0
  store i32 zeroinitializer, i32* %v111
  %v113 = getelementptr [3 x i32], [3 x i32]* %v108, i32 0, i32 1
  store i32 zeroinitializer, i32* %v113
  %v115 = getelementptr [3 x i32], [3 x i32]* %v108, i32 0, i32 2
  store i32 zeroinitializer, i32* %v115
  %v118 = alloca [6 x i32]
  %v121 = getelementptr [6 x i32], [6 x i32]* %v118, i32 0, i32 0
  store i32 zeroinitializer, i32* %v121
  %v123 = getelementptr [6 x i32], [6 x i32]* %v118, i32 0, i32 1
  store i32 zeroinitializer, i32* %v123
  %v125 = getelementptr [6 x i32], [6 x i32]* %v118, i32 0, i32 2
  store i32 zeroinitializer, i32* %v125
  %v127 = getelementptr [6 x i32], [6 x i32]* %v118, i32 0, i32 3
  store i32 zeroinitializer, i32* %v127
  %v129 = getelementptr [6 x i32], [6 x i32]* %v118, i32 0, i32 4
  store i32 zeroinitializer, i32* %v129
  %v131 = getelementptr [6 x i32], [6 x i32]* %v118, i32 0, i32 5
  store i32 zeroinitializer, i32* %v131
  %v134 = alloca [3 x i32]
  %v137 = getelementptr [3 x i32], [3 x i32]* %v134, i32 0, i32 0
  store i32 zeroinitializer, i32* %v137
  %v139 = getelementptr [3 x i32], [3 x i32]* %v134, i32 0, i32 1
  store i32 zeroinitializer, i32* %v139
  %v141 = getelementptr [3 x i32], [3 x i32]* %v134, i32 0, i32 2
  store i32 zeroinitializer, i32* %v141
  %v144 = alloca [3 x i32]
  %v147 = getelementptr [3 x i32], [3 x i32]* %v144, i32 0, i32 0
  store i32 zeroinitializer, i32* %v147
  %v149 = getelementptr [3 x i32], [3 x i32]* %v144, i32 0, i32 1
  store i32 zeroinitializer, i32* %v149
  %v151 = getelementptr [3 x i32], [3 x i32]* %v144, i32 0, i32 2
  store i32 zeroinitializer, i32* %v151
  %v152 = alloca i32
  store i32 zeroinitializer, i32* %v152
  store i32 0, i32* %v152
  %v157 = load i32, i32* %v152
  %bool_159 = icmp slt i32 %v157, 3
  %bool_161 = icmp ne i1 %bool_159, false
  br i1 %bool_161, label %while_entry155, label %next_entry156
while_entry155:
  %v162 = load i32, i32* %v152
  %v163 = getelementptr [3 x i32], [3 x i32]* %v58, i32 0, i32 %v162
  %v164 = load i32, i32* %v152
  store i32 %v164, i32* %v163
  %v165 = load i32, i32* %v152
  %v166 = getelementptr [3 x i32], [3 x i32]* %v68, i32 0, i32 %v165
  %v167 = load i32, i32* %v152
  store i32 %v167, i32* %v166
  %v168 = load i32, i32* %v152
  %v169 = getelementptr [3 x i32], [3 x i32]* %v78, i32 0, i32 %v168
  %v170 = load i32, i32* %v152
  store i32 %v170, i32* %v169
  %v171 = load i32, i32* %v152
  %v172 = getelementptr [3 x i32], [3 x i32]* %v88, i32 0, i32 %v171
  %v173 = load i32, i32* %v152
  store i32 %v173, i32* %v172
  %v174 = load i32, i32* %v152
  %v175 = getelementptr [3 x i32], [3 x i32]* %v98, i32 0, i32 %v174
  %v176 = load i32, i32* %v152
  store i32 %v176, i32* %v175
  %v177 = load i32, i32* %v152
  %v178 = getelementptr [3 x i32], [3 x i32]* %v108, i32 0, i32 %v177
  %v179 = load i32, i32* %v152
  store i32 %v179, i32* %v178
  %v180 = load i32, i32* %v152
  %v182 = add nsw i32 %v180, 1
  store i32 %v182, i32* %v152
  br i1 %bool_161, label %while_entry155, label %next_entry156
next_entry156:
  %v183 = load [3 x i32], [3 x i32]* %v58
  %v184 = load [3 x i32], [3 x i32]* %v88
  %v185 = load [6 x i32], [6 x i32]* %v118
  %v186 = call i32 @concat([3 x i32] %v183, [3 x i32] %v184, [6 x i32] %v185)
  store i32 %v186, i32* %v152
  %v187 = alloca i32
  store i32 zeroinitializer, i32* %v187
  %v191 = load i32, i32* %v152
  %bool_193 = icmp slt i32 %v191, 6
  %bool_195 = icmp ne i1 %bool_193, false
  br i1 %bool_195, label %while_entry189, label %next_entry190
while_entry189:
  %v196 = load i32, i32* %v152
  %v197 = getelementptr [6 x i32], [6 x i32]* %v118, i32 0, i32 %v196
  %v198 = load i32, i32* %v197
  store i32 %v198, i32* %v187
  %v199 = load i32, i32* %v187
  call void @putint(i32 %v199)
  %v201 = load i32, i32* %v152
  %v203 = add nsw i32 %v201, 1
  store i32 %v203, i32* %v152
  br i1 %bool_195, label %while_entry189, label %next_entry190
next_entry190:
  store i32 10, i32* %v187
  %v205 = load i32, i32* %v187
  call void @putch(i32 %v205)
  ret i32 0
}

