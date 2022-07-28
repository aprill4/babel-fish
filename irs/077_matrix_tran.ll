@M9 = global i32 zeroinitializer
@L11 = global i32 zeroinitializer
@N13 = global i32 zeroinitializer
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
define i32 @tran(i32* , i32* , i32* , i32* , i32* , i32* , i32* , i32* , i32* ) {
tran23:
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
  %v38 = getelementptr i32, i32* %v31, i32 0, i32 2
  %v41 = getelementptr i32, i32* %v26, i32 0, i32 1
  %v42 = load i32, i32* %v41
  store i32 %v42, i32* %v38
  %v45 = getelementptr i32, i32* %v32, i32 0, i32 1
  %v48 = getelementptr i32, i32* %v25, i32 0, i32 2
  %v49 = load i32, i32* %v48
  store i32 %v49, i32* %v45
  %v52 = getelementptr i32, i32* %v30, i32 0, i32 1
  %v55 = getelementptr i32, i32* %v25, i32 0, i32 0
  %v56 = load i32, i32* %v55
  store i32 %v56, i32* %v52
  %v59 = getelementptr i32, i32* %v30, i32 0, i32 2
  %v62 = getelementptr i32, i32* %v26, i32 0, i32 0
  %v63 = load i32, i32* %v62
  store i32 %v63, i32* %v59
  %v66 = getelementptr i32, i32* %v31, i32 0, i32 0
  %v69 = getelementptr i32, i32* %v24, i32 0, i32 1
  %v70 = load i32, i32* %v69
  store i32 %v70, i32* %v66
  %v73 = getelementptr i32, i32* %v32, i32 0, i32 0
  %v76 = getelementptr i32, i32* %v24, i32 0, i32 2
  %v77 = load i32, i32* %v76
  store i32 %v77, i32* %v73
  %v80 = getelementptr i32, i32* %v31, i32 0, i32 1
  %v83 = getelementptr i32, i32* %v25, i32 0, i32 1
  %v84 = load i32, i32* %v83
  store i32 %v84, i32* %v80
  %v87 = getelementptr i32, i32* %v32, i32 0, i32 2
  %v90 = getelementptr i32, i32* %v26, i32 0, i32 2
  %v91 = load i32, i32* %v90
  store i32 %v91, i32* %v87
  %v94 = getelementptr i32, i32* %v30, i32 0, i32 0
  %v97 = getelementptr i32, i32* %v24, i32 0, i32 0
  %v98 = load i32, i32* %v97
  store i32 %v98, i32* %v94
  ret i32 0
}
define i32 @main() {
main100:
  store i32 3, i32* @N13
  store i32 3, i32* @M9
  store i32 3, i32* @L11
  %v106 = alloca [3 x i32]
  %v109 = getelementptr [3 x i32], [3 x i32]* %v106, i32 0, i32 0
  store i32 zeroinitializer, i32* %v109
  %v111 = getelementptr [3 x i32], [3 x i32]* %v106, i32 0, i32 1
  store i32 zeroinitializer, i32* %v111
  %v113 = getelementptr [3 x i32], [3 x i32]* %v106, i32 0, i32 2
  store i32 zeroinitializer, i32* %v113
  %v116 = alloca [3 x i32]
  %v119 = getelementptr [3 x i32], [3 x i32]* %v116, i32 0, i32 0
  store i32 zeroinitializer, i32* %v119
  %v121 = getelementptr [3 x i32], [3 x i32]* %v116, i32 0, i32 1
  store i32 zeroinitializer, i32* %v121
  %v123 = getelementptr [3 x i32], [3 x i32]* %v116, i32 0, i32 2
  store i32 zeroinitializer, i32* %v123
  %v126 = alloca [3 x i32]
  %v129 = getelementptr [3 x i32], [3 x i32]* %v126, i32 0, i32 0
  store i32 zeroinitializer, i32* %v129
  %v131 = getelementptr [3 x i32], [3 x i32]* %v126, i32 0, i32 1
  store i32 zeroinitializer, i32* %v131
  %v133 = getelementptr [3 x i32], [3 x i32]* %v126, i32 0, i32 2
  store i32 zeroinitializer, i32* %v133
  %v136 = alloca [3 x i32]
  %v139 = getelementptr [3 x i32], [3 x i32]* %v136, i32 0, i32 0
  store i32 zeroinitializer, i32* %v139
  %v141 = getelementptr [3 x i32], [3 x i32]* %v136, i32 0, i32 1
  store i32 zeroinitializer, i32* %v141
  %v143 = getelementptr [3 x i32], [3 x i32]* %v136, i32 0, i32 2
  store i32 zeroinitializer, i32* %v143
  %v146 = alloca [3 x i32]
  %v149 = getelementptr [3 x i32], [3 x i32]* %v146, i32 0, i32 0
  store i32 zeroinitializer, i32* %v149
  %v151 = getelementptr [3 x i32], [3 x i32]* %v146, i32 0, i32 1
  store i32 zeroinitializer, i32* %v151
  %v153 = getelementptr [3 x i32], [3 x i32]* %v146, i32 0, i32 2
  store i32 zeroinitializer, i32* %v153
  %v156 = alloca [3 x i32]
  %v159 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 0
  store i32 zeroinitializer, i32* %v159
  %v161 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 1
  store i32 zeroinitializer, i32* %v161
  %v163 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 2
  store i32 zeroinitializer, i32* %v163
  %v166 = alloca [6 x i32]
  %v169 = getelementptr [6 x i32], [6 x i32]* %v166, i32 0, i32 0
  store i32 zeroinitializer, i32* %v169
  %v171 = getelementptr [6 x i32], [6 x i32]* %v166, i32 0, i32 1
  store i32 zeroinitializer, i32* %v171
  %v173 = getelementptr [6 x i32], [6 x i32]* %v166, i32 0, i32 2
  store i32 zeroinitializer, i32* %v173
  %v175 = getelementptr [6 x i32], [6 x i32]* %v166, i32 0, i32 3
  store i32 zeroinitializer, i32* %v175
  %v177 = getelementptr [6 x i32], [6 x i32]* %v166, i32 0, i32 4
  store i32 zeroinitializer, i32* %v177
  %v179 = getelementptr [6 x i32], [6 x i32]* %v166, i32 0, i32 5
  store i32 zeroinitializer, i32* %v179
  %v182 = alloca [3 x i32]
  %v185 = getelementptr [3 x i32], [3 x i32]* %v182, i32 0, i32 0
  store i32 zeroinitializer, i32* %v185
  %v187 = getelementptr [3 x i32], [3 x i32]* %v182, i32 0, i32 1
  store i32 zeroinitializer, i32* %v187
  %v189 = getelementptr [3 x i32], [3 x i32]* %v182, i32 0, i32 2
  store i32 zeroinitializer, i32* %v189
  %v192 = alloca [3 x i32]
  %v195 = getelementptr [3 x i32], [3 x i32]* %v192, i32 0, i32 0
  store i32 zeroinitializer, i32* %v195
  %v197 = getelementptr [3 x i32], [3 x i32]* %v192, i32 0, i32 1
  store i32 zeroinitializer, i32* %v197
  %v199 = getelementptr [3 x i32], [3 x i32]* %v192, i32 0, i32 2
  store i32 zeroinitializer, i32* %v199
  %v200 = alloca i32
  store i32 zeroinitializer, i32* %v200
  store i32 0, i32* %v200
  %v205 = load i32, i32* %v200
  %v206 = load i32, i32* @M9
  %bool_207 = icmp slt i32 %v205, %v206
  %bool_209 = icmp ne i1 %bool_207, false
  br i1 %bool_209, label %while_entry203, label %next_entry204
while_entry203:
  %v210 = load i32, i32* %v200
  %v211 = getelementptr [3 x i32], [3 x i32]* %v106, i32 0, i32 %v210
  %v212 = load i32, i32* %v200
  store i32 %v212, i32* %v211
  %v213 = load i32, i32* %v200
  %v214 = getelementptr [3 x i32], [3 x i32]* %v116, i32 0, i32 %v213
  %v215 = load i32, i32* %v200
  store i32 %v215, i32* %v214
  %v216 = load i32, i32* %v200
  %v217 = getelementptr [3 x i32], [3 x i32]* %v126, i32 0, i32 %v216
  %v218 = load i32, i32* %v200
  store i32 %v218, i32* %v217
  %v219 = load i32, i32* %v200
  %v220 = getelementptr [3 x i32], [3 x i32]* %v136, i32 0, i32 %v219
  %v221 = load i32, i32* %v200
  store i32 %v221, i32* %v220
  %v222 = load i32, i32* %v200
  %v223 = getelementptr [3 x i32], [3 x i32]* %v146, i32 0, i32 %v222
  %v224 = load i32, i32* %v200
  store i32 %v224, i32* %v223
  %v225 = load i32, i32* %v200
  %v226 = getelementptr [3 x i32], [3 x i32]* %v156, i32 0, i32 %v225
  %v227 = load i32, i32* %v200
  store i32 %v227, i32* %v226
  %v228 = load i32, i32* %v200
  %v230 = add nsw i32 %v228, 1
  store i32 %v230, i32* %v200
  br i1 %bool_209, label %while_entry203, label %next_entry204
next_entry204:
  %v231 = load [3 x i32], [3 x i32]* %v106
  %v232 = load [3 x i32], [3 x i32]* %v116
  %v233 = load [3 x i32], [3 x i32]* %v126
  %v234 = load [3 x i32], [3 x i32]* %v136
  %v235 = load [3 x i32], [3 x i32]* %v146
  %v236 = load [3 x i32], [3 x i32]* %v156
  %v237 = load [6 x i32], [6 x i32]* %v166
  %v238 = load [3 x i32], [3 x i32]* %v182
  %v239 = load [3 x i32], [3 x i32]* %v192
  %v240 = call i32 @tran([3 x i32] %v231, [3 x i32] %v232, [3 x i32] %v233, [3 x i32] %v234, [3 x i32] %v235, [3 x i32] %v236, [6 x i32] %v237, [3 x i32] %v238, [3 x i32] %v239)
  store i32 %v240, i32* %v200
  %v241 = alloca i32
  store i32 zeroinitializer, i32* %v241
  %v245 = load i32, i32* %v200
  %v246 = load i32, i32* @N13
  %bool_247 = icmp slt i32 %v245, %v246
  %bool_249 = icmp ne i1 %bool_247, false
  br i1 %bool_249, label %while_entry243, label %next_entry244
while_entry243:
  %v250 = load i32, i32* %v200
  %v251 = getelementptr [6 x i32], [6 x i32]* %v166, i32 0, i32 %v250
  %v252 = load i32, i32* %v251
  store i32 %v252, i32* %v241
  %v253 = load i32, i32* %v241
  call void @putint(i32 %v253)
  %v255 = load i32, i32* %v200
  %v257 = add nsw i32 %v255, 1
  store i32 %v257, i32* %v200
  br i1 %bool_249, label %while_entry243, label %next_entry244
next_entry244:
  store i32 10, i32* %v241
  %v259 = load i32, i32* %v241
  call void @putch(i32 %v259)
  store i32 0, i32* %v200
  %v264 = load i32, i32* %v200
  %v265 = load i32, i32* @N13
  %bool_266 = icmp slt i32 %v264, %v265
  %bool_268 = icmp ne i1 %bool_266, false
  br i1 %bool_268, label %while_entry262, label %next_entry263
while_entry262:
  %v269 = load i32, i32* %v200
  %v270 = getelementptr [3 x i32], [3 x i32]* %v182, i32 0, i32 %v269
  %v271 = load i32, i32* %v270
  store i32 %v271, i32* %v241
  %v272 = load i32, i32* %v241
  call void @putint(i32 %v272)
  %v274 = load i32, i32* %v200
  %v276 = add nsw i32 %v274, 1
  store i32 %v276, i32* %v200
  br i1 %bool_268, label %while_entry262, label %next_entry263
next_entry263:
  store i32 10, i32* %v241
  store i32 0, i32* %v200
  %v279 = load i32, i32* %v241
  call void @putch(i32 %v279)
  %v283 = load i32, i32* %v200
  %v284 = load i32, i32* @N13
  %bool_285 = icmp slt i32 %v283, %v284
  %bool_287 = icmp ne i1 %bool_285, false
  br i1 %bool_287, label %while_entry281, label %next_entry282
while_entry281:
  %v288 = load i32, i32* %v200
  %v289 = getelementptr [3 x i32], [3 x i32]* %v192, i32 0, i32 %v288
  %v290 = load i32, i32* %v289
  store i32 %v290, i32* %v241
  %v291 = load i32, i32* %v241
  call void @putint(i32 %v291)
  %v293 = load i32, i32* %v200
  %v295 = add nsw i32 %v293, 1
  store i32 %v295, i32* %v200
  br i1 %bool_287, label %while_entry281, label %next_entry282
next_entry282:
  store i32 10, i32* %v241
  %v297 = load i32, i32* %v241
  call void @putch(i32 %v297)
  ret i32 0
}

