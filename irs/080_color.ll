@maxn10 = constant i32 18
@mod13 = constant i32 1000000000
@dp17 = global <{ [13226976 x i32] }> <{ [13226976 x i32] zeroinitializer }>
@list21 = global <{ [200 x i32] }> <{ [200 x i32] zeroinitializer }>
@cns25 = global <{ [20 x i32] }> <{ [20 x i32] zeroinitializer }>
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
define i32 @equal(i32 , i32 ) {
equal28:
  %v29 = alloca i32
  %v30 = alloca i32
  %v34 = load i32, i32* %v29
  %v35 = load i32, i32* %v30
  %bool_36 = icmp eq i32 %v34, %v35
  br i1 %bool_36, label %if_true_entry31, label %next_entry33
if_true_entry31:
  ret i32 1
next_entry33:
  ret i32 0
}
define i32 @dfs(i32 , i32 , i32 , i32 , i32 , i32 ) {
dfs45:
  %v46 = alloca i32
  %v47 = alloca i32
  %v48 = alloca i32
  %v49 = alloca i32
  %v50 = alloca i32
  %v51 = alloca i32
  %v55 = load i32, i32* %v46
  %v56 = load i32, i32* %v47
  %v57 = load i32, i32* %v48
  %v58 = load i32, i32* %v49
  %v59 = load i32, i32* %v50
  %v60 = load i32, i32* %v51
  %v61 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp17, i32 0, i32 %v55, i32 %v56, i32 %v57, i32 %v58, i32 %v59, i32 %v60
  %v62 = load i32, i32* %v61
  %v65 = sub nsw i32 0, 1
  %bool_66 = icmp ne i32 %v62, %v65
  br i1 %bool_66, label %if_true_entry52, label %next_entry54
if_true_entry52:
  %v67 = load i32, i32* %v46
  %v68 = load i32, i32* %v47
  %v69 = load i32, i32* %v48
  %v70 = load i32, i32* %v49
  %v71 = load i32, i32* %v50
  %v72 = load i32, i32* %v51
  %v73 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp17, i32 0, i32 %v67, i32 %v68, i32 %v69, i32 %v70, i32 %v71, i32 %v72
  %v74 = load i32, i32* %v73
  ret i32 %v74
next_entry54:
  %v78 = load i32, i32* %v46
  %v79 = load i32, i32* %v47
  %v80 = add nsw i32 %v78, %v79
  %v81 = load i32, i32* %v48
  %v82 = add nsw i32 %v80, %v81
  %v83 = load i32, i32* %v49
  %v84 = add nsw i32 %v82, %v83
  %v85 = load i32, i32* %v50
  %v86 = add nsw i32 %v84, %v85
  %bool_88 = icmp eq i32 %v86, 0
  br i1 %bool_88, label %if_true_entry75, label %next_entry77
if_true_entry75:
  ret i32 1
next_entry77:
  %v90 = alloca i32
  store i32 0, i32* %v90
  %bool_96 = icmp ne i32* %v46, float 0.00000000
  br i1 %bool_96, label %if_true_entry92, label %next_entry94
if_true_entry92:
  %v97 = load i32, i32* %v90
  %v98 = load i32, i32* %v46
  %v99 = load i32, i32* %v51
  %v101 = call i32 @equal(i32 %v99, i32 2)
  %v102 = sub nsw i32 %v98, %v101
  %v103 = load i32, i32* %v46
  %v105 = sub nsw i32 %v103, 1
  %v106 = load i32, i32* %v47
  %v107 = load i32, i32* %v48
  %v108 = load i32, i32* %v49
  %v109 = load i32, i32* %v50
  %v111 = call i32 @dfs(i32 %v105, i32 %v106, i32 %v107, i32 %v108, i32 %v109, i32 1)
  %v112 = mul i32 %v102, %v111
  %v113 = add nsw i32 %v97, %v112
  %v114 = srem i32 %v113, 1000000000
  store i32 %v114, i32* %v90
  br label %next_entry94
next_entry94:
  %bool_119 = icmp ne i32* %v47, float 0.00000000
  br i1 %bool_119, label %if_true_entry115, label %next_entry117
if_true_entry115:
  %v120 = load i32, i32* %v90
  %v121 = load i32, i32* %v47
  %v122 = load i32, i32* %v51
  %v124 = call i32 @equal(i32 %v122, i32 3)
  %v125 = sub nsw i32 %v121, %v124
  %v126 = load i32, i32* %v46
  %v128 = add nsw i32 %v126, 1
  %v129 = load i32, i32* %v47
  %v131 = sub nsw i32 %v129, 1
  %v132 = load i32, i32* %v48
  %v133 = load i32, i32* %v49
  %v134 = load i32, i32* %v50
  %v136 = call i32 @dfs(i32 %v128, i32 %v131, i32 %v132, i32 %v133, i32 %v134, i32 2)
  %v137 = mul i32 %v125, %v136
  %v138 = add nsw i32 %v120, %v137
  %v139 = srem i32 %v138, 1000000000
  store i32 %v139, i32* %v90
  br label %next_entry117
next_entry117:
  %bool_144 = icmp ne i32* %v48, float 0.00000000
  br i1 %bool_144, label %if_true_entry140, label %next_entry142
if_true_entry140:
  %v145 = load i32, i32* %v90
  %v146 = load i32, i32* %v48
  %v147 = load i32, i32* %v51
  %v149 = call i32 @equal(i32 %v147, i32 4)
  %v150 = sub nsw i32 %v146, %v149
  %v151 = load i32, i32* %v46
  %v152 = load i32, i32* %v47
  %v154 = add nsw i32 %v152, 1
  %v155 = load i32, i32* %v48
  %v157 = sub nsw i32 %v155, 1
  %v158 = load i32, i32* %v49
  %v159 = load i32, i32* %v50
  %v161 = call i32 @dfs(i32 %v151, i32 %v154, i32 %v157, i32 %v158, i32 %v159, i32 3)
  %v162 = mul i32 %v150, %v161
  %v163 = add nsw i32 %v145, %v162
  %v164 = srem i32 %v163, 1000000000
  store i32 %v164, i32* %v90
  br label %next_entry142
next_entry142:
  %bool_169 = icmp ne i32* %v49, float 0.00000000
  br i1 %bool_169, label %if_true_entry165, label %next_entry167
if_true_entry165:
  %v170 = load i32, i32* %v90
  %v171 = load i32, i32* %v49
  %v172 = load i32, i32* %v51
  %v174 = call i32 @equal(i32 %v172, i32 5)
  %v175 = sub nsw i32 %v171, %v174
  %v176 = load i32, i32* %v46
  %v177 = load i32, i32* %v47
  %v178 = load i32, i32* %v48
  %v180 = add nsw i32 %v178, 1
  %v181 = load i32, i32* %v49
  %v183 = sub nsw i32 %v181, 1
  %v184 = load i32, i32* %v50
  %v186 = call i32 @dfs(i32 %v176, i32 %v177, i32 %v180, i32 %v183, i32 %v184, i32 4)
  %v187 = mul i32 %v175, %v186
  %v188 = add nsw i32 %v170, %v187
  %v189 = srem i32 %v188, 1000000000
  store i32 %v189, i32* %v90
  br label %next_entry167
next_entry167:
  %bool_194 = icmp ne i32* %v50, float 0.00000000
  br i1 %bool_194, label %if_true_entry190, label %next_entry192
if_true_entry190:
  %v195 = load i32, i32* %v90
  %v196 = load i32, i32* %v50
  %v197 = load i32, i32* %v46
  %v198 = load i32, i32* %v47
  %v199 = load i32, i32* %v48
  %v200 = load i32, i32* %v49
  %v202 = add nsw i32 %v200, 1
  %v203 = load i32, i32* %v50
  %v205 = sub nsw i32 %v203, 1
  %v207 = call i32 @dfs(i32 %v197, i32 %v198, i32 %v199, i32 %v202, i32 %v205, i32 5)
  %v208 = mul i32 %v196, %v207
  %v209 = add nsw i32 %v195, %v208
  %v210 = srem i32 %v209, 1000000000
  store i32 %v210, i32* %v90
  br label %next_entry192
next_entry192:
  %v211 = load i32, i32* %v46
  %v212 = load i32, i32* %v47
  %v213 = load i32, i32* %v48
  %v214 = load i32, i32* %v49
  %v215 = load i32, i32* %v50
  %v216 = load i32, i32* %v51
  %v217 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp17, i32 0, i32 %v211, i32 %v212, i32 %v213, i32 %v214, i32 %v215, i32 %v216
  %v218 = load i32, i32* %v90
  %v219 = srem i32 %v218, 1000000000
  store i32 %v219, i32* %v217
  %v220 = load i32, i32* %v46
  %v221 = load i32, i32* %v47
  %v222 = load i32, i32* %v48
  %v223 = load i32, i32* %v49
  %v224 = load i32, i32* %v50
  %v225 = load i32, i32* %v51
  %v226 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp17, i32 0, i32 %v220, i32 %v221, i32 %v222, i32 %v223, i32 %v224, i32 %v225
  %v227 = load i32, i32* %v226
  ret i32 %v227
}
define i32 @main() {
main228:
  %v229 = alloca i32
  %v230 = call i32 @getint()
  store i32 %v230, i32* %v229
  %v231 = alloca i32
  store i32 0, i32* %v231
  %v235 = load i32, i32* %v231
  %bool_236 = icmp slt i32 %v235, 18
  %bool_238 = icmp ne i1 %bool_236, false
  br i1 %bool_238, label %while_entry233, label %next_entry234
while_entry233:
  %v239 = alloca i32
  store i32 0, i32* %v239
  %v243 = load i32, i32* %v239
  %bool_244 = icmp slt i32 %v243, 18
  %bool_246 = icmp ne i1 %bool_244, false
  br i1 %bool_246, label %while_entry241, label %next_entry242
next_entry234:
  store i32 0, i32* %v231
  %v311 = load i32, i32* %v231
  %v312 = load i32, i32* %v229
  %bool_313 = icmp slt i32 %v311, %v312
  %bool_315 = icmp ne i1 %bool_313, false
  br i1 %bool_315, label %while_entry309, label %next_entry310
while_entry241:
  %v247 = alloca i32
  store i32 0, i32* %v247
  %v251 = load i32, i32* %v247
  %bool_252 = icmp slt i32 %v251, 18
  %bool_254 = icmp ne i1 %bool_252, false
  br i1 %bool_254, label %while_entry249, label %next_entry250
next_entry242:
  %v305 = load i32, i32* %v231
  %v307 = add nsw i32 %v305, 1
  store i32 %v307, i32* %v231
  br i1 %bool_238, label %while_entry233, label %next_entry234
while_entry249:
  %v255 = alloca i32
  store i32 0, i32* %v255
  %v259 = load i32, i32* %v255
  %bool_260 = icmp slt i32 %v259, 18
  %bool_262 = icmp ne i1 %bool_260, false
  br i1 %bool_262, label %while_entry257, label %next_entry258
next_entry250:
  %v302 = load i32, i32* %v239
  %v304 = add nsw i32 %v302, 1
  store i32 %v304, i32* %v239
  br i1 %bool_246, label %while_entry241, label %next_entry242
while_entry257:
  %v263 = alloca i32
  store i32 0, i32* %v263
  %v267 = load i32, i32* %v263
  %bool_268 = icmp slt i32 %v267, 18
  %bool_270 = icmp ne i1 %bool_268, false
  br i1 %bool_270, label %while_entry265, label %next_entry266
next_entry258:
  %v299 = load i32, i32* %v247
  %v301 = add nsw i32 %v299, 1
  store i32 %v301, i32* %v247
  br i1 %bool_254, label %while_entry249, label %next_entry250
while_entry265:
  %v271 = alloca i32
  store i32 0, i32* %v271
  %v275 = load i32, i32* %v271
  %bool_277 = icmp slt i32 %v275, 7
  %bool_279 = icmp ne i1 %bool_277, false
  br i1 %bool_279, label %while_entry273, label %next_entry274
next_entry266:
  %v296 = load i32, i32* %v255
  %v298 = add nsw i32 %v296, 1
  store i32 %v298, i32* %v255
  br i1 %bool_262, label %while_entry257, label %next_entry258
while_entry273:
  %v280 = load i32, i32* %v231
  %v281 = load i32, i32* %v239
  %v282 = load i32, i32* %v247
  %v283 = load i32, i32* %v255
  %v284 = load i32, i32* %v263
  %v285 = load i32, i32* %v271
  %v286 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp17, i32 0, i32 %v280, i32 %v281, i32 %v282, i32 %v283, i32 %v284, i32 %v285
  %v289 = sub nsw i32 0, 1
  store i32 %v289, i32* %v286
  %v290 = load i32, i32* %v271
  %v292 = add nsw i32 %v290, 1
  store i32 %v292, i32* %v271
  br i1 %bool_279, label %while_entry273, label %next_entry274
next_entry274:
  %v293 = load i32, i32* %v263
  %v295 = add nsw i32 %v293, 1
  store i32 %v295, i32* %v263
  br i1 %bool_270, label %while_entry265, label %next_entry266
while_entry309:
  %v316 = load i32, i32* %v231
  %v317 = getelementptr [200 x i32], [200 x i32]* @list21, i32 0, i32 %v316
  %v318 = call i32 @getint()
  store i32 %v318, i32* %v317
  %v319 = load i32, i32* %v231
  %v320 = getelementptr [200 x i32], [200 x i32]* @list21, i32 0, i32 %v319
  %v321 = load i32, i32* %v320
  %v322 = getelementptr [20 x i32], [20 x i32]* @cns25, i32 0, i32 %v321
  %v323 = load i32, i32* %v231
  %v324 = getelementptr [200 x i32], [200 x i32]* @list21, i32 0, i32 %v323
  %v325 = load i32, i32* %v324
  %v326 = getelementptr [20 x i32], [20 x i32]* @cns25, i32 0, i32 %v325
  %v327 = load i32, i32* %v326
  %v329 = add nsw i32 %v327, 1
  store i32 %v329, i32* %v322
  %v330 = load i32, i32* %v231
  %v332 = add nsw i32 %v330, 1
  store i32 %v332, i32* %v231
  br i1 %bool_315, label %while_entry309, label %next_entry310
next_entry310:
  %v333 = alloca i32
  %v336 = getelementptr [20 x i32], [20 x i32]* @cns25, i32 0, i32 1
  %v337 = load i32, i32* %v336
  %v340 = getelementptr [20 x i32], [20 x i32]* @cns25, i32 0, i32 2
  %v341 = load i32, i32* %v340
  %v344 = getelementptr [20 x i32], [20 x i32]* @cns25, i32 0, i32 3
  %v345 = load i32, i32* %v344
  %v348 = getelementptr [20 x i32], [20 x i32]* @cns25, i32 0, i32 4
  %v349 = load i32, i32* %v348
  %v352 = getelementptr [20 x i32], [20 x i32]* @cns25, i32 0, i32 5
  %v353 = load i32, i32* %v352
  %v355 = call i32 @dfs(i32 %v337, i32 %v341, i32 %v345, i32 %v349, i32 %v353, i32 0)
  store i32 %v355, i32* %v333
  %v356 = load i32, i32* %v333
  call void @putint(i32 %v356)
  %v358 = load i32, i32* %v333
  ret i32 %v358
}

