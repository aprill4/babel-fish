@N9 = global i32 zeroinitializer
@M11 = global i32 zeroinitializer
@L13 = global i32 zeroinitializer
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
define i32 @sub(i32* , i32* , i32* , i32* , i32* , i32* , i32* , i32* , i32* ) {
sub23:
  %v24 = alloca i32
  %v25 = alloca i32
  %v26 = alloca i32
  %v27 = alloca i32
  %v28 = alloca i32
  %v29 = alloca i32
  %v30 = alloca i32
  %v31 = alloca i32
  %v32 = alloca i32
  %v33 = alloca i32
  store i32 zeroinitializer, i32* %v33
  store i32 0, i32* %v33
  %v38 = load i32, i32* %v33
  %bool_40 = icmp slt i32 %v38, 3
  %bool_42 = icmp ne i1 %bool_40, false
  br i1 %bool_42, label %while_entry36, label %next_entry37
while_entry36:
  %v43 = load i32, i32* %v33
  %v44 = getelementptr i32, i32* %v30, i32 0, i32 %v43
  %v45 = load i32, i32* %v33
  %v46 = getelementptr i32, i32* %v24, i32 0, i32 %v45
  %v47 = load i32, i32* %v46
  %v48 = load i32, i32* %v33
  %v49 = getelementptr i32, i32* %v27, i32 0, i32 %v48
  %v50 = load i32, i32* %v49
  %v51 = sub nsw i32 %v47, %v50
  store i32 %v51, i32* %v44
  %v52 = load i32, i32* %v33
  %v53 = getelementptr i32, i32* %v31, i32 0, i32 %v52
  %v54 = load i32, i32* %v33
  %v55 = getelementptr i32, i32* %v25, i32 0, i32 %v54
  %v56 = load i32, i32* %v55
  %v57 = load i32, i32* %v33
  %v58 = getelementptr i32, i32* %v28, i32 0, i32 %v57
  %v59 = load i32, i32* %v58
  %v60 = sub nsw i32 %v56, %v59
  store i32 %v60, i32* %v53
  %v61 = load i32, i32* %v33
  %v62 = getelementptr i32, i32* %v32, i32 0, i32 %v61
  %v63 = load i32, i32* %v33
  %v64 = getelementptr i32, i32* %v26, i32 0, i32 %v63
  %v65 = load i32, i32* %v64
  %v66 = load i32, i32* %v33
  %v67 = getelementptr i32, i32* %v29, i32 0, i32 %v66
  %v68 = load i32, i32* %v67
  %v69 = sub nsw i32 %v65, %v68
  store i32 %v69, i32* %v62
  %v70 = load i32, i32* %v33
  %v72 = add nsw i32 %v70, 1
  store i32 %v72, i32* %v33
  br i1 %bool_42, label %while_entry36, label %next_entry37
next_entry37:
  ret i32 0
}
define i32 @main() {
main74:
  store i32 3, i32* @N9
  store i32 3, i32* @M11
  store i32 3, i32* @L13
  %v80 = alloca [3 x i32]
  %v83 = getelementptr [3 x i32], [3 x i32]* %v80, i32 0, i32 0
  store i32 zeroinitializer, i32* %v83
  %v85 = getelementptr [3 x i32], [3 x i32]* %v80, i32 0, i32 1
  store i32 zeroinitializer, i32* %v85
  %v87 = getelementptr [3 x i32], [3 x i32]* %v80, i32 0, i32 2
  store i32 zeroinitializer, i32* %v87
  %v90 = alloca [3 x i32]
  %v93 = getelementptr [3 x i32], [3 x i32]* %v90, i32 0, i32 0
  store i32 zeroinitializer, i32* %v93
  %v95 = getelementptr [3 x i32], [3 x i32]* %v90, i32 0, i32 1
  store i32 zeroinitializer, i32* %v95
  %v97 = getelementptr [3 x i32], [3 x i32]* %v90, i32 0, i32 2
  store i32 zeroinitializer, i32* %v97
  %v100 = alloca [3 x i32]
  %v103 = getelementptr [3 x i32], [3 x i32]* %v100, i32 0, i32 0
  store i32 zeroinitializer, i32* %v103
  %v105 = getelementptr [3 x i32], [3 x i32]* %v100, i32 0, i32 1
  store i32 zeroinitializer, i32* %v105
  %v107 = getelementptr [3 x i32], [3 x i32]* %v100, i32 0, i32 2
  store i32 zeroinitializer, i32* %v107
  %v110 = alloca [3 x i32]
  %v113 = getelementptr [3 x i32], [3 x i32]* %v110, i32 0, i32 0
  store i32 zeroinitializer, i32* %v113
  %v115 = getelementptr [3 x i32], [3 x i32]* %v110, i32 0, i32 1
  store i32 zeroinitializer, i32* %v115
  %v117 = getelementptr [3 x i32], [3 x i32]* %v110, i32 0, i32 2
  store i32 zeroinitializer, i32* %v117
  %v120 = alloca [3 x i32]
  %v123 = getelementptr [3 x i32], [3 x i32]* %v120, i32 0, i32 0
  store i32 zeroinitializer, i32* %v123
  %v125 = getelementptr [3 x i32], [3 x i32]* %v120, i32 0, i32 1
  store i32 zeroinitializer, i32* %v125
  %v127 = getelementptr [3 x i32], [3 x i32]* %v120, i32 0, i32 2
  store i32 zeroinitializer, i32* %v127
  %v130 = alloca [3 x i32]
  %v133 = getelementptr [3 x i32], [3 x i32]* %v130, i32 0, i32 0
  store i32 zeroinitializer, i32* %v133
  %v135 = getelementptr [3 x i32], [3 x i32]* %v130, i32 0, i32 1
  store i32 zeroinitializer, i32* %v135
  %v137 = getelementptr [3 x i32], [3 x i32]* %v130, i32 0, i32 2
  store i32 zeroinitializer, i32* %v137
  %v140 = alloca [6 x i32]
  %v143 = getelementptr [6 x i32], [6 x i32]* %v140, i32 0, i32 0
  store i32 zeroinitializer, i32* %v143
  %v145 = getelementptr [6 x i32], [6 x i32]* %v140, i32 0, i32 1
  store i32 zeroinitializer, i32* %v145
  %v147 = getelementptr [6 x i32], [6 x i32]* %v140, i32 0, i32 2
  store i32 zeroinitializer, i32* %v147
  %v149 = getelementptr [6 x i32], [6 x i32]* %v140, i32 0, i32 3
  store i32 zeroinitializer, i32* %v149
  %v151 = getelementptr [6 x i32], [6 x i32]* %v140, i32 0, i32 4
  store i32 zeroinitializer, i32* %v151
  %v153 = getelementptr [6 x i32], [6 x i32]* %v140, i32 0, i32 5
  store i32 zeroinitializer, i32* %v153
  %v156 = alloca [3 x i32]
  %v159 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 0
  store i32 zeroinitializer, i32* %v159
  %v161 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 1
  store i32 zeroinitializer, i32* %v161
  %v163 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 2
  store i32 zeroinitializer, i32* %v163
  %v166 = alloca [3 x i32]
  %v169 = getelementptr [3 x i32], [3 x i32]* %v166, i32 0, i32 0
  store i32 zeroinitializer, i32* %v169
  %v171 = getelementptr [3 x i32], [3 x i32]* %v166, i32 0, i32 1
  store i32 zeroinitializer, i32* %v171
  %v173 = getelementptr [3 x i32], [3 x i32]* %v166, i32 0, i32 2
  store i32 zeroinitializer, i32* %v173
  %v174 = alloca i32
  store i32 zeroinitializer, i32* %v174
  store i32 0, i32* %v174
  %v179 = load i32, i32* %v174
  %bool_181 = icmp slt i32 %v179, 3
  %bool_183 = icmp ne i1 %bool_181, false
  br i1 %bool_183, label %while_entry177, label %next_entry178
while_entry177:
  %v184 = load i32, i32* %v174
  %v185 = getelementptr [3 x i32], [3 x i32]* %v80, i32 0, i32 %v184
  %v186 = load i32, i32* %v174
  store i32 %v186, i32* %v185
  %v187 = load i32, i32* %v174
  %v188 = getelementptr [3 x i32], [3 x i32]* %v90, i32 0, i32 %v187
  %v189 = load i32, i32* %v174
  store i32 %v189, i32* %v188
  %v190 = load i32, i32* %v174
  %v191 = getelementptr [3 x i32], [3 x i32]* %v100, i32 0, i32 %v190
  %v192 = load i32, i32* %v174
  store i32 %v192, i32* %v191
  %v193 = load i32, i32* %v174
  %v194 = getelementptr [3 x i32], [3 x i32]* %v110, i32 0, i32 %v193
  %v195 = load i32, i32* %v174
  store i32 %v195, i32* %v194
  %v196 = load i32, i32* %v174
  %v197 = getelementptr [3 x i32], [3 x i32]* %v120, i32 0, i32 %v196
  %v198 = load i32, i32* %v174
  store i32 %v198, i32* %v197
  %v199 = load i32, i32* %v174
  %v200 = getelementptr [3 x i32], [3 x i32]* %v130, i32 0, i32 %v199
  %v201 = load i32, i32* %v174
  store i32 %v201, i32* %v200
  %v202 = load i32, i32* %v174
  %v204 = add nsw i32 %v202, 1
  store i32 %v204, i32* %v174
  br i1 %bool_183, label %while_entry177, label %next_entry178
next_entry178:
  %v205 = load [3 x i32], [3 x i32]* %v80
  %v206 = load [3 x i32], [3 x i32]* %v90
  %v207 = load [3 x i32], [3 x i32]* %v100
  %v208 = load [3 x i32], [3 x i32]* %v110
  %v209 = load [3 x i32], [3 x i32]* %v120
  %v210 = load [3 x i32], [3 x i32]* %v130
  %v211 = load [6 x i32], [6 x i32]* %v140
  %v212 = load [3 x i32], [3 x i32]* %v156
  %v213 = load [3 x i32], [3 x i32]* %v166
  %v214 = call i32 @sub([3 x i32] %v205, [3 x i32] %v206, [3 x i32] %v207, [3 x i32] %v208, [3 x i32] %v209, [3 x i32] %v210, [6 x i32] %v211, [3 x i32] %v212, [3 x i32] %v213)
  store i32 %v214, i32* %v174
  %v215 = alloca i32
  store i32 zeroinitializer, i32* %v215
  %v219 = load i32, i32* %v174
  %bool_221 = icmp slt i32 %v219, 3
  %bool_223 = icmp ne i1 %bool_221, false
  br i1 %bool_223, label %while_entry217, label %next_entry218
while_entry217:
  %v224 = load i32, i32* %v174
  %v225 = getelementptr [6 x i32], [6 x i32]* %v140, i32 0, i32 %v224
  %v226 = load i32, i32* %v225
  store i32 %v226, i32* %v215
  %v227 = load i32, i32* %v215
  call void @putint(i32 %v227)
  %v229 = load i32, i32* %v174
  %v231 = add nsw i32 %v229, 1
  store i32 %v231, i32* %v174
  br i1 %bool_223, label %while_entry217, label %next_entry218
next_entry218:
  store i32 10, i32* %v215
  store i32 0, i32* %v174
  %v234 = load i32, i32* %v215
  call void @putch(i32 %v234)
  %v238 = load i32, i32* %v174
  %bool_240 = icmp slt i32 %v238, 3
  %bool_242 = icmp ne i1 %bool_240, false
  br i1 %bool_242, label %while_entry236, label %next_entry237
while_entry236:
  %v243 = load i32, i32* %v174
  %v244 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 %v243
  %v245 = load i32, i32* %v244
  store i32 %v245, i32* %v215
  %v246 = load i32, i32* %v215
  call void @putint(i32 %v246)
  %v248 = load i32, i32* %v174
  %v250 = add nsw i32 %v248, 1
  store i32 %v250, i32* %v174
  br i1 %bool_242, label %while_entry236, label %next_entry237
next_entry237:
  store i32 10, i32* %v215
  store i32 0, i32* %v174
  %v253 = load i32, i32* %v215
  call void @putch(i32 %v253)
  %v257 = load i32, i32* %v174
  %bool_259 = icmp slt i32 %v257, 3
  %bool_261 = icmp ne i1 %bool_259, false
  br i1 %bool_261, label %while_entry255, label %next_entry256
while_entry255:
  %v262 = load i32, i32* %v174
  %v263 = getelementptr [3 x i32], [3 x i32]* %v166, i32 0, i32 %v262
  %v264 = load i32, i32* %v263
  store i32 %v264, i32* %v215
  %v265 = load i32, i32* %v215
  call void @putint(i32 %v265)
  %v267 = load i32, i32* %v174
  %v269 = add nsw i32 %v267, 1
  store i32 %v269, i32* %v174
  br i1 %bool_261, label %while_entry255, label %next_entry256
next_entry256:
  store i32 10, i32* %v215
  %v271 = load i32, i32* %v215
  call void @putch(i32 %v271)
  ret i32 0
}

