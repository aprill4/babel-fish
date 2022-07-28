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
define i32 @mul(i32* , i32* , i32* , i32* , i32* , i32* , i32* , i32* , i32* ) {
mul23:
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
  %v38 = getelementptr i32, i32* %v30, i32 0, i32 0
  %v41 = getelementptr i32, i32* %v24, i32 0, i32 0
  %v42 = load i32, i32* %v41
  %v45 = getelementptr i32, i32* %v27, i32 0, i32 0
  %v46 = load i32, i32* %v45
  %v47 = mul i32 %v42, %v46
  %v50 = getelementptr i32, i32* %v24, i32 0, i32 1
  %v51 = load i32, i32* %v50
  %v54 = getelementptr i32, i32* %v28, i32 0, i32 0
  %v55 = load i32, i32* %v54
  %v56 = mul i32 %v51, %v55
  %v57 = add nsw i32 %v47, %v56
  %v60 = getelementptr i32, i32* %v24, i32 0, i32 2
  %v61 = load i32, i32* %v60
  %v64 = getelementptr i32, i32* %v29, i32 0, i32 0
  %v65 = load i32, i32* %v64
  %v66 = mul i32 %v61, %v65
  %v67 = add nsw i32 %v57, %v66
  store i32 %v67, i32* %v38
  %v70 = getelementptr i32, i32* %v30, i32 0, i32 1
  %v73 = getelementptr i32, i32* %v24, i32 0, i32 0
  %v74 = load i32, i32* %v73
  %v77 = getelementptr i32, i32* %v27, i32 0, i32 1
  %v78 = load i32, i32* %v77
  %v79 = mul i32 %v74, %v78
  %v82 = getelementptr i32, i32* %v24, i32 0, i32 1
  %v83 = load i32, i32* %v82
  %v86 = getelementptr i32, i32* %v28, i32 0, i32 1
  %v87 = load i32, i32* %v86
  %v88 = mul i32 %v83, %v87
  %v89 = add nsw i32 %v79, %v88
  %v92 = getelementptr i32, i32* %v24, i32 0, i32 2
  %v93 = load i32, i32* %v92
  %v96 = getelementptr i32, i32* %v29, i32 0, i32 1
  %v97 = load i32, i32* %v96
  %v98 = mul i32 %v93, %v97
  %v99 = add nsw i32 %v89, %v98
  store i32 %v99, i32* %v70
  %v102 = getelementptr i32, i32* %v30, i32 0, i32 2
  %v105 = getelementptr i32, i32* %v24, i32 0, i32 0
  %v106 = load i32, i32* %v105
  %v109 = getelementptr i32, i32* %v27, i32 0, i32 2
  %v110 = load i32, i32* %v109
  %v111 = mul i32 %v106, %v110
  %v114 = getelementptr i32, i32* %v24, i32 0, i32 1
  %v115 = load i32, i32* %v114
  %v118 = getelementptr i32, i32* %v28, i32 0, i32 2
  %v119 = load i32, i32* %v118
  %v120 = mul i32 %v115, %v119
  %v121 = add nsw i32 %v111, %v120
  %v124 = getelementptr i32, i32* %v24, i32 0, i32 2
  %v125 = load i32, i32* %v124
  %v128 = getelementptr i32, i32* %v29, i32 0, i32 2
  %v129 = load i32, i32* %v128
  %v130 = mul i32 %v125, %v129
  %v131 = add nsw i32 %v121, %v130
  store i32 %v131, i32* %v102
  %v134 = getelementptr i32, i32* %v31, i32 0, i32 0
  %v137 = getelementptr i32, i32* %v25, i32 0, i32 0
  %v138 = load i32, i32* %v137
  %v141 = getelementptr i32, i32* %v27, i32 0, i32 0
  %v142 = load i32, i32* %v141
  %v143 = mul i32 %v138, %v142
  %v146 = getelementptr i32, i32* %v25, i32 0, i32 1
  %v147 = load i32, i32* %v146
  %v150 = getelementptr i32, i32* %v28, i32 0, i32 0
  %v151 = load i32, i32* %v150
  %v152 = mul i32 %v147, %v151
  %v153 = add nsw i32 %v143, %v152
  %v156 = getelementptr i32, i32* %v25, i32 0, i32 2
  %v157 = load i32, i32* %v156
  %v160 = getelementptr i32, i32* %v29, i32 0, i32 0
  %v161 = load i32, i32* %v160
  %v162 = mul i32 %v157, %v161
  %v163 = add nsw i32 %v153, %v162
  store i32 %v163, i32* %v134
  %v166 = getelementptr i32, i32* %v31, i32 0, i32 1
  %v169 = getelementptr i32, i32* %v25, i32 0, i32 0
  %v170 = load i32, i32* %v169
  %v173 = getelementptr i32, i32* %v27, i32 0, i32 1
  %v174 = load i32, i32* %v173
  %v175 = mul i32 %v170, %v174
  %v178 = getelementptr i32, i32* %v25, i32 0, i32 1
  %v179 = load i32, i32* %v178
  %v182 = getelementptr i32, i32* %v28, i32 0, i32 1
  %v183 = load i32, i32* %v182
  %v184 = mul i32 %v179, %v183
  %v185 = add nsw i32 %v175, %v184
  %v188 = getelementptr i32, i32* %v25, i32 0, i32 2
  %v189 = load i32, i32* %v188
  %v192 = getelementptr i32, i32* %v29, i32 0, i32 1
  %v193 = load i32, i32* %v192
  %v194 = mul i32 %v189, %v193
  %v195 = add nsw i32 %v185, %v194
  store i32 %v195, i32* %v166
  %v198 = getelementptr i32, i32* %v31, i32 0, i32 2
  %v201 = getelementptr i32, i32* %v25, i32 0, i32 0
  %v202 = load i32, i32* %v201
  %v205 = getelementptr i32, i32* %v27, i32 0, i32 2
  %v206 = load i32, i32* %v205
  %v207 = mul i32 %v202, %v206
  %v210 = getelementptr i32, i32* %v25, i32 0, i32 1
  %v211 = load i32, i32* %v210
  %v214 = getelementptr i32, i32* %v28, i32 0, i32 2
  %v215 = load i32, i32* %v214
  %v216 = mul i32 %v211, %v215
  %v217 = add nsw i32 %v207, %v216
  %v220 = getelementptr i32, i32* %v25, i32 0, i32 2
  %v221 = load i32, i32* %v220
  %v224 = getelementptr i32, i32* %v29, i32 0, i32 2
  %v225 = load i32, i32* %v224
  %v226 = mul i32 %v221, %v225
  %v227 = add nsw i32 %v217, %v226
  store i32 %v227, i32* %v198
  %v230 = getelementptr i32, i32* %v32, i32 0, i32 0
  %v233 = getelementptr i32, i32* %v26, i32 0, i32 0
  %v234 = load i32, i32* %v233
  %v237 = getelementptr i32, i32* %v27, i32 0, i32 0
  %v238 = load i32, i32* %v237
  %v239 = mul i32 %v234, %v238
  %v242 = getelementptr i32, i32* %v26, i32 0, i32 1
  %v243 = load i32, i32* %v242
  %v246 = getelementptr i32, i32* %v28, i32 0, i32 0
  %v247 = load i32, i32* %v246
  %v248 = mul i32 %v243, %v247
  %v249 = add nsw i32 %v239, %v248
  %v252 = getelementptr i32, i32* %v26, i32 0, i32 2
  %v253 = load i32, i32* %v252
  %v256 = getelementptr i32, i32* %v29, i32 0, i32 0
  %v257 = load i32, i32* %v256
  %v258 = mul i32 %v253, %v257
  %v259 = add nsw i32 %v249, %v258
  store i32 %v259, i32* %v230
  %v262 = getelementptr i32, i32* %v32, i32 0, i32 1
  %v265 = getelementptr i32, i32* %v26, i32 0, i32 0
  %v266 = load i32, i32* %v265
  %v269 = getelementptr i32, i32* %v27, i32 0, i32 1
  %v270 = load i32, i32* %v269
  %v271 = mul i32 %v266, %v270
  %v274 = getelementptr i32, i32* %v26, i32 0, i32 1
  %v275 = load i32, i32* %v274
  %v278 = getelementptr i32, i32* %v28, i32 0, i32 1
  %v279 = load i32, i32* %v278
  %v280 = mul i32 %v275, %v279
  %v281 = add nsw i32 %v271, %v280
  %v284 = getelementptr i32, i32* %v26, i32 0, i32 2
  %v285 = load i32, i32* %v284
  %v288 = getelementptr i32, i32* %v29, i32 0, i32 1
  %v289 = load i32, i32* %v288
  %v290 = mul i32 %v285, %v289
  %v291 = add nsw i32 %v281, %v290
  store i32 %v291, i32* %v262
  %v294 = getelementptr i32, i32* %v32, i32 0, i32 2
  %v297 = getelementptr i32, i32* %v26, i32 0, i32 0
  %v298 = load i32, i32* %v297
  %v301 = getelementptr i32, i32* %v27, i32 0, i32 2
  %v302 = load i32, i32* %v301
  %v303 = mul i32 %v298, %v302
  %v306 = getelementptr i32, i32* %v26, i32 0, i32 1
  %v307 = load i32, i32* %v306
  %v310 = getelementptr i32, i32* %v28, i32 0, i32 2
  %v311 = load i32, i32* %v310
  %v312 = mul i32 %v307, %v311
  %v313 = add nsw i32 %v303, %v312
  %v316 = getelementptr i32, i32* %v26, i32 0, i32 2
  %v317 = load i32, i32* %v316
  %v320 = getelementptr i32, i32* %v29, i32 0, i32 2
  %v321 = load i32, i32* %v320
  %v322 = mul i32 %v317, %v321
  %v323 = add nsw i32 %v313, %v322
  store i32 %v323, i32* %v294
  ret i32 0
}
define i32 @main() {
main325:
  store i32 3, i32* @N13
  store i32 3, i32* @M9
  store i32 3, i32* @L11
  %v331 = alloca [3 x i32]
  %v334 = getelementptr [3 x i32], [3 x i32]* %v331, i32 0, i32 0
  store i32 zeroinitializer, i32* %v334
  %v336 = getelementptr [3 x i32], [3 x i32]* %v331, i32 0, i32 1
  store i32 zeroinitializer, i32* %v336
  %v338 = getelementptr [3 x i32], [3 x i32]* %v331, i32 0, i32 2
  store i32 zeroinitializer, i32* %v338
  %v341 = alloca [3 x i32]
  %v344 = getelementptr [3 x i32], [3 x i32]* %v341, i32 0, i32 0
  store i32 zeroinitializer, i32* %v344
  %v346 = getelementptr [3 x i32], [3 x i32]* %v341, i32 0, i32 1
  store i32 zeroinitializer, i32* %v346
  %v348 = getelementptr [3 x i32], [3 x i32]* %v341, i32 0, i32 2
  store i32 zeroinitializer, i32* %v348
  %v351 = alloca [3 x i32]
  %v354 = getelementptr [3 x i32], [3 x i32]* %v351, i32 0, i32 0
  store i32 zeroinitializer, i32* %v354
  %v356 = getelementptr [3 x i32], [3 x i32]* %v351, i32 0, i32 1
  store i32 zeroinitializer, i32* %v356
  %v358 = getelementptr [3 x i32], [3 x i32]* %v351, i32 0, i32 2
  store i32 zeroinitializer, i32* %v358
  %v361 = alloca [3 x i32]
  %v364 = getelementptr [3 x i32], [3 x i32]* %v361, i32 0, i32 0
  store i32 zeroinitializer, i32* %v364
  %v366 = getelementptr [3 x i32], [3 x i32]* %v361, i32 0, i32 1
  store i32 zeroinitializer, i32* %v366
  %v368 = getelementptr [3 x i32], [3 x i32]* %v361, i32 0, i32 2
  store i32 zeroinitializer, i32* %v368
  %v371 = alloca [3 x i32]
  %v374 = getelementptr [3 x i32], [3 x i32]* %v371, i32 0, i32 0
  store i32 zeroinitializer, i32* %v374
  %v376 = getelementptr [3 x i32], [3 x i32]* %v371, i32 0, i32 1
  store i32 zeroinitializer, i32* %v376
  %v378 = getelementptr [3 x i32], [3 x i32]* %v371, i32 0, i32 2
  store i32 zeroinitializer, i32* %v378
  %v381 = alloca [3 x i32]
  %v384 = getelementptr [3 x i32], [3 x i32]* %v381, i32 0, i32 0
  store i32 zeroinitializer, i32* %v384
  %v386 = getelementptr [3 x i32], [3 x i32]* %v381, i32 0, i32 1
  store i32 zeroinitializer, i32* %v386
  %v388 = getelementptr [3 x i32], [3 x i32]* %v381, i32 0, i32 2
  store i32 zeroinitializer, i32* %v388
  %v391 = alloca [6 x i32]
  %v394 = getelementptr [6 x i32], [6 x i32]* %v391, i32 0, i32 0
  store i32 zeroinitializer, i32* %v394
  %v396 = getelementptr [6 x i32], [6 x i32]* %v391, i32 0, i32 1
  store i32 zeroinitializer, i32* %v396
  %v398 = getelementptr [6 x i32], [6 x i32]* %v391, i32 0, i32 2
  store i32 zeroinitializer, i32* %v398
  %v400 = getelementptr [6 x i32], [6 x i32]* %v391, i32 0, i32 3
  store i32 zeroinitializer, i32* %v400
  %v402 = getelementptr [6 x i32], [6 x i32]* %v391, i32 0, i32 4
  store i32 zeroinitializer, i32* %v402
  %v404 = getelementptr [6 x i32], [6 x i32]* %v391, i32 0, i32 5
  store i32 zeroinitializer, i32* %v404
  %v407 = alloca [3 x i32]
  %v410 = getelementptr [3 x i32], [3 x i32]* %v407, i32 0, i32 0
  store i32 zeroinitializer, i32* %v410
  %v412 = getelementptr [3 x i32], [3 x i32]* %v407, i32 0, i32 1
  store i32 zeroinitializer, i32* %v412
  %v414 = getelementptr [3 x i32], [3 x i32]* %v407, i32 0, i32 2
  store i32 zeroinitializer, i32* %v414
  %v417 = alloca [3 x i32]
  %v420 = getelementptr [3 x i32], [3 x i32]* %v417, i32 0, i32 0
  store i32 zeroinitializer, i32* %v420
  %v422 = getelementptr [3 x i32], [3 x i32]* %v417, i32 0, i32 1
  store i32 zeroinitializer, i32* %v422
  %v424 = getelementptr [3 x i32], [3 x i32]* %v417, i32 0, i32 2
  store i32 zeroinitializer, i32* %v424
  %v425 = alloca i32
  store i32 zeroinitializer, i32* %v425
  store i32 0, i32* %v425
  %v430 = load i32, i32* %v425
  %v431 = load i32, i32* @M9
  %bool_432 = icmp slt i32 %v430, %v431
  %bool_434 = icmp ne i1 %bool_432, false
  br i1 %bool_434, label %while_entry428, label %next_entry429
while_entry428:
  %v435 = load i32, i32* %v425
  %v436 = getelementptr [3 x i32], [3 x i32]* %v331, i32 0, i32 %v435
  %v437 = load i32, i32* %v425
  store i32 %v437, i32* %v436
  %v438 = load i32, i32* %v425
  %v439 = getelementptr [3 x i32], [3 x i32]* %v341, i32 0, i32 %v438
  %v440 = load i32, i32* %v425
  store i32 %v440, i32* %v439
  %v441 = load i32, i32* %v425
  %v442 = getelementptr [3 x i32], [3 x i32]* %v351, i32 0, i32 %v441
  %v443 = load i32, i32* %v425
  store i32 %v443, i32* %v442
  %v444 = load i32, i32* %v425
  %v445 = getelementptr [3 x i32], [3 x i32]* %v361, i32 0, i32 %v444
  %v446 = load i32, i32* %v425
  store i32 %v446, i32* %v445
  %v447 = load i32, i32* %v425
  %v448 = getelementptr [3 x i32], [3 x i32]* %v371, i32 0, i32 %v447
  %v449 = load i32, i32* %v425
  store i32 %v449, i32* %v448
  %v450 = load i32, i32* %v425
  %v451 = getelementptr [3 x i32], [3 x i32]* %v381, i32 0, i32 %v450
  %v452 = load i32, i32* %v425
  store i32 %v452, i32* %v451
  %v453 = load i32, i32* %v425
  %v455 = add nsw i32 %v453, 1
  store i32 %v455, i32* %v425
  br i1 %bool_434, label %while_entry428, label %next_entry429
next_entry429:
  %v456 = load [3 x i32], [3 x i32]* %v331
  %v457 = load [3 x i32], [3 x i32]* %v341
  %v458 = load [3 x i32], [3 x i32]* %v351
  %v459 = load [3 x i32], [3 x i32]* %v361
  %v460 = load [3 x i32], [3 x i32]* %v371
  %v461 = load [3 x i32], [3 x i32]* %v381
  %v462 = load [6 x i32], [6 x i32]* %v391
  %v463 = load [3 x i32], [3 x i32]* %v407
  %v464 = load [3 x i32], [3 x i32]* %v417
  %v465 = call i32 @mul([3 x i32] %v456, [3 x i32] %v457, [3 x i32] %v458, [3 x i32] %v459, [3 x i32] %v460, [3 x i32] %v461, [6 x i32] %v462, [3 x i32] %v463, [3 x i32] %v464)
  store i32 %v465, i32* %v425
  %v466 = alloca i32
  store i32 zeroinitializer, i32* %v466
  %v470 = load i32, i32* %v425
  %v471 = load i32, i32* @N13
  %bool_472 = icmp slt i32 %v470, %v471
  %bool_474 = icmp ne i1 %bool_472, false
  br i1 %bool_474, label %while_entry468, label %next_entry469
while_entry468:
  %v475 = load i32, i32* %v425
  %v476 = getelementptr [6 x i32], [6 x i32]* %v391, i32 0, i32 %v475
  %v477 = load i32, i32* %v476
  store i32 %v477, i32* %v466
  %v478 = load i32, i32* %v466
  call void @putint(i32 %v478)
  %v480 = load i32, i32* %v425
  %v482 = add nsw i32 %v480, 1
  store i32 %v482, i32* %v425
  br i1 %bool_474, label %while_entry468, label %next_entry469
next_entry469:
  store i32 10, i32* %v466
  store i32 0, i32* %v425
  %v485 = load i32, i32* %v466
  call void @putch(i32 %v485)
  %v489 = load i32, i32* %v425
  %v490 = load i32, i32* @N13
  %bool_491 = icmp slt i32 %v489, %v490
  %bool_493 = icmp ne i1 %bool_491, false
  br i1 %bool_493, label %while_entry487, label %next_entry488
while_entry487:
  %v494 = load i32, i32* %v425
  %v495 = getelementptr [3 x i32], [3 x i32]* %v407, i32 0, i32 %v494
  %v496 = load i32, i32* %v495
  store i32 %v496, i32* %v466
  %v497 = load i32, i32* %v466
  call void @putint(i32 %v497)
  %v499 = load i32, i32* %v425
  %v501 = add nsw i32 %v499, 1
  store i32 %v501, i32* %v425
  br i1 %bool_493, label %while_entry487, label %next_entry488
next_entry488:
  store i32 10, i32* %v466
  store i32 0, i32* %v425
  %v504 = load i32, i32* %v466
  call void @putch(i32 %v504)
  %v508 = load i32, i32* %v425
  %v509 = load i32, i32* @N13
  %bool_510 = icmp slt i32 %v508, %v509
  %bool_512 = icmp ne i1 %bool_510, false
  br i1 %bool_512, label %while_entry506, label %next_entry507
while_entry506:
  %v513 = load i32, i32* %v425
  %v514 = getelementptr [3 x i32], [3 x i32]* %v417, i32 0, i32 %v513
  %v515 = load i32, i32* %v514
  store i32 %v515, i32* %v466
  %v516 = load i32, i32* %v466
  call void @putint(i32 %v516)
  %v518 = load i32, i32* %v425
  %v520 = add nsw i32 %v518, 1
  store i32 %v520, i32* %v425
  br i1 %bool_512, label %while_entry506, label %next_entry507
next_entry507:
  store i32 10, i32* %v466
  %v522 = load i32, i32* %v466
  call void @putch(i32 %v522)
  ret i32 0
}

