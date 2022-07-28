@len10 = constant i32 20
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
define i32 @main() {
main11:
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  %v14 = alloca i32
  store i32 zeroinitializer, i32* %v14
  %v16 = alloca i32
  store i32 zeroinitializer, i32* %v16
  %v18 = alloca i32
  store i32 zeroinitializer, i32* %v18
  %v20 = alloca i32
  store i32 zeroinitializer, i32* %v20
  %v42 = alloca [20 x i32]
  %v45 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 0
  store i32 1, i32* %v45
  %v47 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 1
  store i32 2, i32* %v47
  %v49 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 2
  store i32 3, i32* %v49
  %v51 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 3
  store i32 4, i32* %v51
  %v53 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 4
  store i32 5, i32* %v53
  %v55 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 5
  store i32 6, i32* %v55
  %v57 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 6
  store i32 7, i32* %v57
  %v59 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 7
  store i32 8, i32* %v59
  %v61 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 8
  store i32 9, i32* %v61
  %v63 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 9
  store i32 0, i32* %v63
  %v65 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 10
  store i32 1, i32* %v65
  %v67 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 11
  store i32 2, i32* %v67
  %v69 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 12
  store i32 3, i32* %v69
  %v71 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 13
  store i32 4, i32* %v71
  %v73 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 14
  store i32 5, i32* %v73
  %v75 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 15
  store i32 6, i32* %v75
  %v77 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 16
  store i32 7, i32* %v77
  %v79 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 17
  store i32 8, i32* %v79
  %v81 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 18
  store i32 9, i32* %v81
  %v83 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 19
  store i32 0, i32* %v83
  %v104 = alloca [20 x i32]
  %v107 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 0
  store i32 2, i32* %v107
  %v109 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 1
  store i32 3, i32* %v109
  %v111 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 2
  store i32 4, i32* %v111
  %v113 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 3
  store i32 2, i32* %v113
  %v115 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 4
  store i32 5, i32* %v115
  %v117 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 5
  store i32 7, i32* %v117
  %v119 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 6
  store i32 9, i32* %v119
  %v121 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 7
  store i32 9, i32* %v121
  %v123 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 8
  store i32 0, i32* %v123
  %v125 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 9
  store i32 1, i32* %v125
  %v127 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 10
  store i32 9, i32* %v127
  %v129 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 11
  store i32 8, i32* %v129
  %v131 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 12
  store i32 7, i32* %v131
  %v133 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 13
  store i32 6, i32* %v133
  %v135 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 14
  store i32 4, i32* %v135
  %v137 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 15
  store i32 3, i32* %v137
  %v139 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 16
  store i32 2, i32* %v139
  %v141 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 17
  store i32 1, i32* %v141
  %v143 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 18
  store i32 2, i32* %v143
  %v145 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 19
  store i32 2, i32* %v145
  %v146 = alloca i32
  %v147 = load i32, i32* @len10
  store i32 %v147, i32* %v146
  %v148 = alloca i32
  %v149 = load i32, i32* @len10
  store i32 %v149, i32* %v148
  %v153 = alloca [25 x i32]
  %v156 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 0
  store i32 zeroinitializer, i32* %v156
  %v158 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 1
  store i32 zeroinitializer, i32* %v158
  %v160 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 2
  store i32 zeroinitializer, i32* %v160
  %v162 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 3
  store i32 zeroinitializer, i32* %v162
  %v164 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 4
  store i32 zeroinitializer, i32* %v164
  %v166 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 5
  store i32 zeroinitializer, i32* %v166
  %v168 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 6
  store i32 zeroinitializer, i32* %v168
  %v170 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 7
  store i32 zeroinitializer, i32* %v170
  %v172 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 8
  store i32 zeroinitializer, i32* %v172
  %v174 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 9
  store i32 zeroinitializer, i32* %v174
  %v176 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 10
  store i32 zeroinitializer, i32* %v176
  %v178 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 11
  store i32 zeroinitializer, i32* %v178
  %v180 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 12
  store i32 zeroinitializer, i32* %v180
  %v182 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 13
  store i32 zeroinitializer, i32* %v182
  %v184 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 14
  store i32 zeroinitializer, i32* %v184
  %v186 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 15
  store i32 zeroinitializer, i32* %v186
  %v188 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 16
  store i32 zeroinitializer, i32* %v188
  %v190 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 17
  store i32 zeroinitializer, i32* %v190
  %v192 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 18
  store i32 zeroinitializer, i32* %v192
  %v194 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 19
  store i32 zeroinitializer, i32* %v194
  %v196 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 20
  store i32 zeroinitializer, i32* %v196
  %v198 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 21
  store i32 zeroinitializer, i32* %v198
  %v200 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 22
  store i32 zeroinitializer, i32* %v200
  %v202 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 23
  store i32 zeroinitializer, i32* %v202
  %v204 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 24
  store i32 zeroinitializer, i32* %v204
  %v208 = alloca [25 x i32]
  %v211 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 0
  store i32 zeroinitializer, i32* %v211
  %v213 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 1
  store i32 zeroinitializer, i32* %v213
  %v215 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 2
  store i32 zeroinitializer, i32* %v215
  %v217 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 3
  store i32 zeroinitializer, i32* %v217
  %v219 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 4
  store i32 zeroinitializer, i32* %v219
  %v221 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 5
  store i32 zeroinitializer, i32* %v221
  %v223 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 6
  store i32 zeroinitializer, i32* %v223
  %v225 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 7
  store i32 zeroinitializer, i32* %v225
  %v227 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 8
  store i32 zeroinitializer, i32* %v227
  %v229 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 9
  store i32 zeroinitializer, i32* %v229
  %v231 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 10
  store i32 zeroinitializer, i32* %v231
  %v233 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 11
  store i32 zeroinitializer, i32* %v233
  %v235 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 12
  store i32 zeroinitializer, i32* %v235
  %v237 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 13
  store i32 zeroinitializer, i32* %v237
  %v239 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 14
  store i32 zeroinitializer, i32* %v239
  %v241 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 15
  store i32 zeroinitializer, i32* %v241
  %v243 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 16
  store i32 zeroinitializer, i32* %v243
  %v245 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 17
  store i32 zeroinitializer, i32* %v245
  %v247 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 18
  store i32 zeroinitializer, i32* %v247
  %v249 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 19
  store i32 zeroinitializer, i32* %v249
  %v251 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 20
  store i32 zeroinitializer, i32* %v251
  %v253 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 21
  store i32 zeroinitializer, i32* %v253
  %v255 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 22
  store i32 zeroinitializer, i32* %v255
  %v257 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 23
  store i32 zeroinitializer, i32* %v257
  %v259 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 24
  store i32 zeroinitializer, i32* %v259
  %v263 = alloca [40 x i32]
  %v266 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 0
  store i32 zeroinitializer, i32* %v266
  %v268 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 1
  store i32 zeroinitializer, i32* %v268
  %v270 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 2
  store i32 zeroinitializer, i32* %v270
  %v272 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 3
  store i32 zeroinitializer, i32* %v272
  %v274 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 4
  store i32 zeroinitializer, i32* %v274
  %v276 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 5
  store i32 zeroinitializer, i32* %v276
  %v278 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 6
  store i32 zeroinitializer, i32* %v278
  %v280 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 7
  store i32 zeroinitializer, i32* %v280
  %v282 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 8
  store i32 zeroinitializer, i32* %v282
  %v284 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 9
  store i32 zeroinitializer, i32* %v284
  %v286 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 10
  store i32 zeroinitializer, i32* %v286
  %v288 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 11
  store i32 zeroinitializer, i32* %v288
  %v290 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 12
  store i32 zeroinitializer, i32* %v290
  %v292 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 13
  store i32 zeroinitializer, i32* %v292
  %v294 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 14
  store i32 zeroinitializer, i32* %v294
  %v296 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 15
  store i32 zeroinitializer, i32* %v296
  %v298 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 16
  store i32 zeroinitializer, i32* %v298
  %v300 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 17
  store i32 zeroinitializer, i32* %v300
  %v302 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 18
  store i32 zeroinitializer, i32* %v302
  %v304 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 19
  store i32 zeroinitializer, i32* %v304
  %v306 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 20
  store i32 zeroinitializer, i32* %v306
  %v308 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 21
  store i32 zeroinitializer, i32* %v308
  %v310 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 22
  store i32 zeroinitializer, i32* %v310
  %v312 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 23
  store i32 zeroinitializer, i32* %v312
  %v314 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 24
  store i32 zeroinitializer, i32* %v314
  %v316 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 25
  store i32 zeroinitializer, i32* %v316
  %v318 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 26
  store i32 zeroinitializer, i32* %v318
  %v320 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 27
  store i32 zeroinitializer, i32* %v320
  %v322 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 28
  store i32 zeroinitializer, i32* %v322
  %v324 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 29
  store i32 zeroinitializer, i32* %v324
  %v326 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 30
  store i32 zeroinitializer, i32* %v326
  %v328 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 31
  store i32 zeroinitializer, i32* %v328
  %v330 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 32
  store i32 zeroinitializer, i32* %v330
  %v332 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 33
  store i32 zeroinitializer, i32* %v332
  %v334 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 34
  store i32 zeroinitializer, i32* %v334
  %v336 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 35
  store i32 zeroinitializer, i32* %v336
  %v338 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 36
  store i32 zeroinitializer, i32* %v338
  %v340 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 37
  store i32 zeroinitializer, i32* %v340
  %v342 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 38
  store i32 zeroinitializer, i32* %v342
  %v344 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 39
  store i32 zeroinitializer, i32* %v344
  store i32 0, i32* %v12
  %v348 = load i32, i32* %v12
  %v349 = load i32, i32* %v146
  %bool_350 = icmp slt i32 %v348, %v349
  %bool_352 = icmp ne i1 %bool_350, false
  br i1 %bool_352, label %while_entry346, label %next_entry347
while_entry346:
  %v353 = load i32, i32* %v12
  %v354 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 %v353
  %v355 = load i32, i32* %v12
  %v356 = getelementptr [20 x i32], [20 x i32]* %v42, i32 0, i32 %v355
  %v357 = load i32, i32* %v356
  store i32 %v357, i32* %v354
  %v358 = load i32, i32* %v12
  %v360 = add nsw i32 %v358, 1
  store i32 %v360, i32* %v12
  br i1 %bool_352, label %while_entry346, label %next_entry347
next_entry347:
  store i32 0, i32* %v12
  %v364 = load i32, i32* %v12
  %v365 = load i32, i32* %v148
  %bool_366 = icmp slt i32 %v364, %v365
  %bool_368 = icmp ne i1 %bool_366, false
  br i1 %bool_368, label %while_entry362, label %next_entry363
while_entry362:
  %v369 = load i32, i32* %v12
  %v370 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 %v369
  %v371 = load i32, i32* %v12
  %v372 = getelementptr [20 x i32], [20 x i32]* %v104, i32 0, i32 %v371
  %v373 = load i32, i32* %v372
  store i32 %v373, i32* %v370
  %v374 = load i32, i32* %v12
  %v376 = add nsw i32 %v374, 1
  store i32 %v376, i32* %v12
  br i1 %bool_368, label %while_entry362, label %next_entry363
next_entry363:
  %v377 = load i32, i32* %v146
  %v378 = load i32, i32* %v148
  %v379 = add nsw i32 %v377, %v378
  %v381 = sub nsw i32 %v379, 1
  store i32 %v381, i32* %v18
  store i32 0, i32* %v12
  %v385 = load i32, i32* %v12
  %v386 = load i32, i32* %v18
  %bool_387 = icmp sle i32 %v385, %v386
  %bool_389 = icmp ne i1 %bool_387, false
  br i1 %bool_389, label %while_entry383, label %next_entry384
while_entry383:
  %v390 = load i32, i32* %v12
  %v391 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 %v390
  store i32 0, i32* %v391
  %v393 = load i32, i32* %v12
  %v395 = add nsw i32 %v393, 1
  store i32 %v395, i32* %v12
  br i1 %bool_389, label %while_entry383, label %next_entry384
next_entry384:
  store i32 0, i32* %v20
  %v397 = load i32, i32* %v148
  %v399 = sub nsw i32 %v397, 1
  store i32 %v399, i32* %v12
  %v402 = load i32, i32* %v12
  %v405 = sub nsw i32 0, 1
  %bool_406 = icmp sgt i32 %v402, %v405
  %bool_408 = icmp ne i1 %bool_406, false
  br i1 %bool_408, label %while_entry400, label %next_entry401
while_entry400:
  %v409 = load i32, i32* %v12
  %v410 = getelementptr [25 x i32], [25 x i32]* %v208, i32 0, i32 %v409
  %v411 = load i32, i32* %v410
  store i32 %v411, i32* %v16
  %v412 = load i32, i32* %v146
  %v414 = sub nsw i32 %v412, 1
  store i32 %v414, i32* %v14
  %v417 = load i32, i32* %v14
  %v420 = sub nsw i32 0, 1
  %bool_421 = icmp sgt i32 %v417, %v420
  %bool_423 = icmp ne i1 %bool_421, false
  br i1 %bool_423, label %while_entry415, label %next_entry416
next_entry401:
  %v477 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 0
  %v478 = load i32, i32* %v477
  %bool_480 = icmp ne i32 %v478, 0
  br i1 %bool_480, label %if_true_entry472, label %next_entry474
while_entry415:
  %v424 = load i32, i32* %v18
  %v425 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 %v424
  %v426 = load i32, i32* %v425
  %v427 = load i32, i32* %v16
  %v428 = load i32, i32* %v14
  %v429 = getelementptr [25 x i32], [25 x i32]* %v153, i32 0, i32 %v428
  %v430 = load i32, i32* %v429
  %v431 = mul i32 %v427, %v430
  %v432 = add nsw i32 %v426, %v431
  store i32 %v432, i32* %v20
  %v436 = load i32, i32* %v20
  %bool_438 = icmp sge i32 %v436, 10
  br i1 %bool_438, label %if_true_entry433, label %if_false_entry434
next_entry416:
  %v464 = load i32, i32* %v18
  %v465 = load i32, i32* %v146
  %v466 = add nsw i32 %v464, %v465
  %v468 = sub nsw i32 %v466, 1
  store i32 %v468, i32* %v18
  %v469 = load i32, i32* %v12
  %v471 = sub nsw i32 %v469, 1
  store i32 %v471, i32* %v12
  br i1 %bool_408, label %while_entry400, label %next_entry401
if_true_entry433:
  %v439 = load i32, i32* %v18
  %v440 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 %v439
  %v441 = load i32, i32* %v20
  store i32 %v441, i32* %v440
  %v442 = load i32, i32* %v18
  %v444 = sub nsw i32 %v442, 1
  %v445 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 %v444
  %v446 = load i32, i32* %v18
  %v448 = sub nsw i32 %v446, 1
  %v449 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 %v448
  %v450 = load i32, i32* %v449
  %v451 = load i32, i32* %v20
  %v453 = sdiv i32 %v451, 10
  %v454 = add nsw i32 %v450, %v453
  store i32 %v454, i32* %v445
  br label %next_entry435
if_false_entry434:
  %v455 = load i32, i32* %v18
  %v456 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 %v455
  %v457 = load i32, i32* %v20
  store i32 %v457, i32* %v456
  br label %next_entry435
next_entry435:
  %v458 = load i32, i32* %v14
  %v460 = sub nsw i32 %v458, 1
  store i32 %v460, i32* %v14
  %v461 = load i32, i32* %v18
  %v463 = sub nsw i32 %v461, 1
  store i32 %v463, i32* %v18
  br i1 %bool_423, label %while_entry415, label %next_entry416
if_true_entry472:
  %v483 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 0
  %v484 = load i32, i32* %v483
  call void @putint(i32 %v484)
  br label %next_entry474
next_entry474:
  store i32 1, i32* %v12
  %v489 = load i32, i32* %v12
  %v490 = load i32, i32* %v146
  %v491 = load i32, i32* %v148
  %v492 = add nsw i32 %v490, %v491
  %v494 = sub nsw i32 %v492, 1
  %bool_495 = icmp sle i32 %v489, %v494
  %bool_497 = icmp ne i1 %bool_495, false
  br i1 %bool_497, label %while_entry487, label %next_entry488
while_entry487:
  %v498 = load i32, i32* %v12
  %v499 = getelementptr [40 x i32], [40 x i32]* %v263, i32 0, i32 %v498
  %v500 = load i32, i32* %v499
  call void @putint(i32 %v500)
  %v502 = load i32, i32* %v12
  %v504 = add nsw i32 %v502, 1
  store i32 %v504, i32* %v12
  br i1 %bool_497, label %while_entry487, label %next_entry488
next_entry488:
  ret i32 0
}

