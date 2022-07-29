@ints11 = global <{ [10000 x i32] }> <{ [10000 x i32] zeroinitializer }>
@intt13 = global i32 zeroinitializer
@chas17 = global <{ [10000 x i32] }> <{ [10000 x i32] zeroinitializer }>
@chat19 = global i32 zeroinitializer
@i22 = global i32 0
@ii25 = global i32 1
@c27 = global i32 zeroinitializer
@get31 = global <{ [10000 x i32] }> <{ [10000 x i32] zeroinitializer }>
@get235 = global <{ [10000 x i32] }> <{ [10000 x i32] zeroinitializer }>
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
define i32 @isdigit(i32 ) {
isdigit37:
  %v38 = alloca i32
  %v44 = load i32, i32* %v38
  %bool_46 = icmp sge i32 %v44, 48
  %bool_48 = icmp ne i1 %bool_46, zeroinitializer
  br i1 %bool_48, label %l42, label %r43
if_true_entry39:
  ret i32 1
next_entry41:
  ret i32 0
l42:
  %v49 = load i32, i32* %v38
  %bool_51 = icmp sle i32 %v49, 57
  %bool_53 = icmp ne i1 %bool_51, zeroinitializer
  br i1 %bool_53, label %if_true_entry39, label %r43
r43:
  br label %next_entry41
}
define i32 @power(i32 , i32 ) {
power58:
  %v59 = alloca i32
  %v60 = alloca i32
  %v61 = alloca i32
  store i32 1, i32* %v61
  %v65 = load i32, i32* %v60
  %bool_67 = icmp ne i32 %v65, 0
  %bool_69 = icmp ne i1 %bool_67, false
  br i1 %bool_69, label %while_entry63, label %next_entry64
while_entry63:
  %v70 = load i32, i32* %v61
  %v71 = load i32, i32* %v59
  %v72 = mul i32 %v70, %v71
  store i32 %v72, i32* %v61
  %v73 = load i32, i32* %v60
  %v75 = sub nsw i32 %v73, 1
  store i32 %v75, i32* %v60
  br i1 %bool_69, label %while_entry63, label %next_entry64
next_entry64:
  %v76 = load i32, i32* %v61
  ret i32 %v76
}
define i32 @getstr(i32* ) {
getstr78:
  %v79 = alloca i32
  %v80 = alloca i32
  %v81 = call i32 @getch()
  store i32 %v81, i32* %v80
  %v82 = alloca i32
  store i32 0, i32* %v82
  %v88 = load i32, i32* %v80
  %bool_90 = icmp ne i32 %v88, 13
  %bool_92 = icmp ne i1 %bool_90, zeroinitializer
  br i1 %bool_92, label %l86, label %r87
while_entry84:
next_entry85:
  %v98 = load i32, i32* %v82
  ret i32 %v98
l86:
  %v93 = load i32, i32* %v80
  %bool_95 = icmp ne i32 %v93, 10
  %bool_97 = icmp ne i1 %bool_95, zeroinitializer
  br i1 %bool_97, label %while_entry84, label %r87
r87:
  br label %next_entry85
}
define void @intpush(i32 ) {
intpush100:
  %v101 = alloca i32
  %v102 = load i32, i32* @intt13
  %v104 = add nsw i32 %v102, 1
  store i32 %v104, i32* @intt13
  %v105 = load i32, i32* @intt13
  %v106 = getelementptr [10000 x i32], [10000 x i32]* @ints11, i32 0, i32 %v105
  %v107 = load i32, i32* %v101
  store i32 %v107, i32* %v106
  ret void
}
define void @chapush(i32 ) {
chapush109:
  %v110 = alloca i32
  %v111 = load i32, i32* @chat19
  %v113 = add nsw i32 %v111, 1
  store i32 %v113, i32* @chat19
  %v114 = load i32, i32* @chat19
  %v115 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v114
  %v116 = load i32, i32* %v110
  store i32 %v116, i32* %v115
  ret void
}
define i32 @intpop() {
intpop117:
  %v118 = load i32, i32* @intt13
  %v120 = sub nsw i32 %v118, 1
  store i32 %v120, i32* @intt13
  %v121 = load i32, i32* @intt13
  %v123 = add nsw i32 %v121, 1
  %v124 = getelementptr [10000 x i32], [10000 x i32]* @ints11, i32 0, i32 %v123
  %v125 = load i32, i32* %v124
  ret i32 %v125
}
define i32 @chapop() {
chapop126:
  %v127 = load i32, i32* @chat19
  %v129 = sub nsw i32 %v127, 1
  store i32 %v129, i32* @chat19
  %v130 = load i32, i32* @chat19
  %v132 = add nsw i32 %v130, 1
  %v133 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v132
  %v134 = load i32, i32* %v133
  ret i32 %v134
}
define void @intadd(i32 ) {
intadd136:
  %v137 = alloca i32
  %v138 = load i32, i32* @intt13
  %v139 = getelementptr [10000 x i32], [10000 x i32]* @ints11, i32 0, i32 %v138
  %v140 = load i32, i32* @intt13
  %v141 = getelementptr [10000 x i32], [10000 x i32]* @ints11, i32 0, i32 %v140
  %v142 = load i32, i32* %v141
  %v144 = mul i32 %v142, 10
  store i32 %v144, i32* %v139
  %v145 = load i32, i32* @intt13
  %v146 = getelementptr [10000 x i32], [10000 x i32]* @ints11, i32 0, i32 %v145
  %v147 = load i32, i32* @intt13
  %v148 = getelementptr [10000 x i32], [10000 x i32]* @ints11, i32 0, i32 %v147
  %v149 = load i32, i32* %v148
  %v150 = load i32, i32* %v137
  %v151 = add nsw i32 %v149, %v150
  store i32 %v151, i32* %v146
  ret void
}
define i32 @find() {
find152:
  %v153 = call i32 @chapop()
  store i32 %v153, i32* @c27
  %v154 = load i32, i32* @ii25
  %v155 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v154
  store i32 32, i32* %v155
  %v157 = load i32, i32* @ii25
  %v159 = add nsw i32 %v157, 1
  %v160 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v159
  %v161 = load i32, i32* @c27
  store i32 %v161, i32* %v160
  %v162 = load i32, i32* @ii25
  %v164 = add nsw i32 %v162, 2
  store i32 %v164, i32* @ii25
  %v168 = load i32, i32* @chat19
  %bool_170 = icmp eq i32 %v168, 0
  br i1 %bool_170, label %if_true_entry165, label %next_entry167
if_true_entry165:
  ret i32 0
next_entry167:
  ret i32 1
}
define i32 @main() {
main173:
  store i32 0, i32* @intt13
  store i32 0, i32* @chat19
  %v176 = alloca i32
  %v177 = load [10000 x i32], [10000 x i32]* @get31
  %v178 = call i32 @getstr([10000 x i32] %v177)
  store i32 %v178, i32* %v176
  %v181 = load i32, i32* @i22
  %v182 = load i32, i32* %v176
  %bool_183 = icmp slt i32 %v181, %v182
  %bool_185 = icmp ne i1 %bool_183, false
  br i1 %bool_185, label %while_entry179, label %next_entry180
while_entry179:
  %v189 = load i32, i32* @i22
  %v190 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v189
  %v191 = load i32, i32* %v190
  %v192 = call i32 @isdigit(i32 %v191)
  %bool_194 = icmp eq i32 %v192, 1
  br i1 %bool_194, label %if_true_entry186, label %if_false_entry187
next_entry180:
  %v528 = load i32, i32* @chat19
  %bool_530 = icmp sgt i32 %v528, 0
  %bool_532 = icmp ne i1 %bool_530, false
  br i1 %bool_532, label %while_entry526, label %next_entry527
if_true_entry186:
  %v195 = load i32, i32* @ii25
  %v196 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v195
  %v197 = load i32, i32* @i22
  %v198 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v197
  %v199 = load i32, i32* %v198
  store i32 %v199, i32* %v196
  %v200 = load i32, i32* @ii25
  %v202 = add nsw i32 %v200, 1
  store i32 %v202, i32* @ii25
  br label %next_entry188
if_false_entry187:
  %v206 = load i32, i32* @i22
  %v207 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v206
  %v208 = load i32, i32* %v207
  %bool_210 = icmp eq i32 %v208, 40
  br i1 %bool_210, label %if_true_entry203, label %next_entry205
next_entry188:
  %v523 = load i32, i32* @i22
  %v525 = add nsw i32 %v523, 1
  store i32 %v525, i32* @i22
  br i1 %bool_185, label %while_entry179, label %next_entry180
if_true_entry203:
  call void @chapush(i32 40)
  br label %next_entry205
next_entry205:
  %v216 = load i32, i32* @i22
  %v217 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v216
  %v218 = load i32, i32* %v217
  %bool_220 = icmp eq i32 %v218, 94
  br i1 %bool_220, label %if_true_entry213, label %next_entry215
if_true_entry213:
  call void @chapush(i32 94)
  br label %next_entry215
next_entry215:
  %v226 = load i32, i32* @i22
  %v227 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v226
  %v228 = load i32, i32* %v227
  %bool_230 = icmp eq i32 %v228, 41
  br i1 %bool_230, label %if_true_entry223, label %next_entry225
if_true_entry223:
  %v231 = call i32 @chapop()
  store i32 %v231, i32* @c27
  %v234 = load i32, i32* @c27
  %bool_236 = icmp ne i32 %v234, 40
  %bool_238 = icmp ne i1 %bool_236, false
  br i1 %bool_238, label %while_entry232, label %next_entry233
next_entry225:
  %v254 = load i32, i32* @i22
  %v255 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v254
  %v256 = load i32, i32* %v255
  %bool_258 = icmp eq i32 %v256, 43
  br i1 %bool_258, label %if_true_entry251, label %next_entry253
while_entry232:
  %v239 = load i32, i32* @ii25
  %v240 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v239
  store i32 32, i32* %v240
  %v242 = load i32, i32* @ii25
  %v244 = add nsw i32 %v242, 1
  %v245 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v244
  %v246 = load i32, i32* @c27
  store i32 %v246, i32* %v245
  %v247 = load i32, i32* @ii25
  %v249 = add nsw i32 %v247, 2
  store i32 %v249, i32* @ii25
  %v250 = call i32 @chapop()
  store i32 %v250, i32* @c27
  br i1 %bool_238, label %while_entry232, label %next_entry233
next_entry233:
  br label %next_entry225
if_true_entry251:
  %v271 = load i32, i32* @chat19
  %v272 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v271
  %v273 = load i32, i32* %v272
  %bool_275 = icmp eq i32 %v273, 43
  %bool_277 = icmp ne i1 %bool_275, zeroinitializer
  br i1 %bool_277, label %l269, label %r270
next_entry253:
  %v318 = load i32, i32* @i22
  %v319 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v318
  %v320 = load i32, i32* %v319
  %bool_322 = icmp eq i32 %v320, 45
  br i1 %bool_322, label %if_true_entry315, label %next_entry317
while_entry259:
next_entry260:
  call void @chapush(i32 43)
  br label %next_entry253
l261:
  br label %while_entry179
r262:
  %v306 = load i32, i32* @chat19
  %v307 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v306
  %v308 = load i32, i32* %v307
  %bool_310 = icmp eq i32 %v308, 94
  %bool_312 = icmp ne i1 %bool_310, zeroinitializer
  br i1 %bool_312, label %l261, label %next_entry260
l263:
  br label %while_entry259
r264:
  %v299 = load i32, i32* @chat19
  %v300 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v299
  %v301 = load i32, i32* %v300
  %bool_303 = icmp eq i32 %v301, 37
  %bool_305 = icmp ne i1 %bool_303, zeroinitializer
  br i1 %bool_305, label %l263, label %r262
l265:
  br label %while_entry179
r266:
  %v292 = load i32, i32* @chat19
  %v293 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v292
  %v294 = load i32, i32* %v293
  %bool_296 = icmp eq i32 %v294, 47
  %bool_298 = icmp ne i1 %bool_296, zeroinitializer
  br i1 %bool_298, label %l265, label %r264
l267:
  br label %while_entry259
r268:
  %v285 = load i32, i32* @chat19
  %v286 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v285
  %v287 = load i32, i32* %v286
  %bool_289 = icmp eq i32 %v287, 42
  %bool_291 = icmp ne i1 %bool_289, zeroinitializer
  br i1 %bool_291, label %l267, label %r266
l269:
  br label %while_entry179
r270:
  %v278 = load i32, i32* @chat19
  %v279 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v278
  %v280 = load i32, i32* %v279
  %bool_282 = icmp eq i32 %v280, 45
  %bool_284 = icmp ne i1 %bool_282, zeroinitializer
  br i1 %bool_284, label %l269, label %r268
if_true_entry315:
  %v335 = load i32, i32* @chat19
  %v336 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v335
  %v337 = load i32, i32* %v336
  %bool_339 = icmp eq i32 %v337, 43
  %bool_341 = icmp ne i1 %bool_339, zeroinitializer
  br i1 %bool_341, label %l333, label %r334
next_entry317:
  %v382 = load i32, i32* @i22
  %v383 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v382
  %v384 = load i32, i32* %v383
  %bool_386 = icmp eq i32 %v384, 42
  br i1 %bool_386, label %if_true_entry379, label %next_entry381
while_entry323:
next_entry324:
  call void @chapush(i32 45)
  br label %next_entry317
l325:
  br label %while_entry179
r326:
  %v370 = load i32, i32* @chat19
  %v371 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v370
  %v372 = load i32, i32* %v371
  %bool_374 = icmp eq i32 %v372, 94
  %bool_376 = icmp ne i1 %bool_374, zeroinitializer
  br i1 %bool_376, label %l325, label %next_entry324
l327:
  br label %while_entry323
r328:
  %v363 = load i32, i32* @chat19
  %v364 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v363
  %v365 = load i32, i32* %v364
  %bool_367 = icmp eq i32 %v365, 37
  %bool_369 = icmp ne i1 %bool_367, zeroinitializer
  br i1 %bool_369, label %l327, label %r326
l329:
  br label %while_entry179
r330:
  %v356 = load i32, i32* @chat19
  %v357 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v356
  %v358 = load i32, i32* %v357
  %bool_360 = icmp eq i32 %v358, 47
  %bool_362 = icmp ne i1 %bool_360, zeroinitializer
  br i1 %bool_362, label %l329, label %r328
l331:
  br label %while_entry323
r332:
  %v349 = load i32, i32* @chat19
  %v350 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v349
  %v351 = load i32, i32* %v350
  %bool_353 = icmp eq i32 %v351, 42
  %bool_355 = icmp ne i1 %bool_353, zeroinitializer
  br i1 %bool_355, label %l331, label %r330
l333:
  br label %while_entry179
r334:
  %v342 = load i32, i32* @chat19
  %v343 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v342
  %v344 = load i32, i32* %v343
  %bool_346 = icmp eq i32 %v344, 45
  %bool_348 = icmp ne i1 %bool_346, zeroinitializer
  br i1 %bool_348, label %l333, label %r332
if_true_entry379:
  %v395 = load i32, i32* @chat19
  %v396 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v395
  %v397 = load i32, i32* %v396
  %bool_399 = icmp eq i32 %v397, 42
  %bool_401 = icmp ne i1 %bool_399, zeroinitializer
  br i1 %bool_401, label %l393, label %r394
next_entry381:
  %v428 = load i32, i32* @i22
  %v429 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v428
  %v430 = load i32, i32* %v429
  %bool_432 = icmp eq i32 %v430, 47
  br i1 %bool_432, label %if_true_entry425, label %next_entry427
while_entry387:
next_entry388:
  call void @chapush(i32 42)
  br label %next_entry381
l389:
  br label %while_entry179
r390:
  %v416 = load i32, i32* @chat19
  %v417 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v416
  %v418 = load i32, i32* %v417
  %bool_420 = icmp eq i32 %v418, 94
  %bool_422 = icmp ne i1 %bool_420, zeroinitializer
  br i1 %bool_422, label %l389, label %next_entry388
l391:
  br label %while_entry387
r392:
  %v409 = load i32, i32* @chat19
  %v410 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v409
  %v411 = load i32, i32* %v410
  %bool_413 = icmp eq i32 %v411, 37
  %bool_415 = icmp ne i1 %bool_413, zeroinitializer
  br i1 %bool_415, label %l391, label %r390
l393:
  br label %while_entry179
r394:
  %v402 = load i32, i32* @chat19
  %v403 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v402
  %v404 = load i32, i32* %v403
  %bool_406 = icmp eq i32 %v404, 47
  %bool_408 = icmp ne i1 %bool_406, zeroinitializer
  br i1 %bool_408, label %l393, label %r392
if_true_entry425:
  %v441 = load i32, i32* @chat19
  %v442 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v441
  %v443 = load i32, i32* %v442
  %bool_445 = icmp eq i32 %v443, 42
  %bool_447 = icmp ne i1 %bool_445, zeroinitializer
  br i1 %bool_447, label %l439, label %r440
next_entry427:
  %v474 = load i32, i32* @i22
  %v475 = getelementptr [10000 x i32], [10000 x i32]* @get31, i32 0, i32 %v474
  %v476 = load i32, i32* %v475
  %bool_478 = icmp eq i32 %v476, 37
  br i1 %bool_478, label %if_true_entry471, label %next_entry473
while_entry433:
next_entry434:
  call void @chapush(i32 47)
  br label %next_entry427
l435:
  br label %while_entry179
r436:
  %v462 = load i32, i32* @chat19
  %v463 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v462
  %v464 = load i32, i32* %v463
  %bool_466 = icmp eq i32 %v464, 94
  %bool_468 = icmp ne i1 %bool_466, zeroinitializer
  br i1 %bool_468, label %l435, label %next_entry434
l437:
  br label %while_entry433
r438:
  %v455 = load i32, i32* @chat19
  %v456 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v455
  %v457 = load i32, i32* %v456
  %bool_459 = icmp eq i32 %v457, 37
  %bool_461 = icmp ne i1 %bool_459, zeroinitializer
  br i1 %bool_461, label %l437, label %r436
l439:
  br label %while_entry179
r440:
  %v448 = load i32, i32* @chat19
  %v449 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v448
  %v450 = load i32, i32* %v449
  %bool_452 = icmp eq i32 %v450, 47
  %bool_454 = icmp ne i1 %bool_452, zeroinitializer
  br i1 %bool_454, label %l439, label %r438
if_true_entry471:
  %v487 = load i32, i32* @chat19
  %v488 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v487
  %v489 = load i32, i32* %v488
  %bool_491 = icmp eq i32 %v489, 42
  %bool_493 = icmp ne i1 %bool_491, zeroinitializer
  br i1 %bool_493, label %l485, label %r486
next_entry473:
  %v517 = load i32, i32* @ii25
  %v518 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v517
  store i32 32, i32* %v518
  %v520 = load i32, i32* @ii25
  %v522 = add nsw i32 %v520, 1
  store i32 %v522, i32* @ii25
  br label %next_entry188
while_entry479:
next_entry480:
  call void @chapush(i32 37)
  br label %next_entry473
l481:
  br label %while_entry179
r482:
  %v508 = load i32, i32* @chat19
  %v509 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v508
  %v510 = load i32, i32* %v509
  %bool_512 = icmp eq i32 %v510, 94
  %bool_514 = icmp ne i1 %bool_512, zeroinitializer
  br i1 %bool_514, label %l481, label %next_entry480
l483:
  br label %while_entry479
r484:
  %v501 = load i32, i32* @chat19
  %v502 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v501
  %v503 = load i32, i32* %v502
  %bool_505 = icmp eq i32 %v503, 37
  %bool_507 = icmp ne i1 %bool_505, zeroinitializer
  br i1 %bool_507, label %l483, label %r482
l485:
  br label %while_entry179
r486:
  %v494 = load i32, i32* @chat19
  %v495 = getelementptr [10000 x i32], [10000 x i32]* @chas17, i32 0, i32 %v494
  %v496 = load i32, i32* %v495
  %bool_498 = icmp eq i32 %v496, 47
  %bool_500 = icmp ne i1 %bool_498, zeroinitializer
  br i1 %bool_500, label %l485, label %r484
while_entry526:
  %v533 = alloca i32
  %v534 = call i32 @chapop()
  store i32 %v534, i32* %v533
  %v535 = load i32, i32* @ii25
  %v536 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v535
  store i32 32, i32* %v536
  %v538 = load i32, i32* @ii25
  %v540 = add nsw i32 %v538, 1
  %v541 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v540
  %v542 = load i32, i32* %v533
  store i32 %v542, i32* %v541
  %v543 = load i32, i32* @ii25
  %v545 = add nsw i32 %v543, 2
  store i32 %v545, i32* @ii25
  br i1 %bool_532, label %while_entry526, label %next_entry527
next_entry527:
  %v546 = load i32, i32* @ii25
  %v547 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v546
  store i32 64, i32* %v547
  store i32 1, i32* @i22
  %v552 = load i32, i32* @i22
  %v553 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v552
  %v554 = load i32, i32* %v553
  %bool_556 = icmp ne i32 %v554, 64
  %bool_558 = icmp ne i1 %bool_556, false
  br i1 %bool_558, label %while_entry550, label %next_entry551
while_entry550:
  %v572 = load i32, i32* @i22
  %v573 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v572
  %v574 = load i32, i32* %v573
  %bool_576 = icmp eq i32 %v574, 43
  %bool_578 = icmp ne i1 %bool_576, zeroinitializer
  br i1 %bool_578, label %l570, label %r571
next_entry551:
  %v735 = getelementptr [10000 x i32], [10000 x i32]* @ints11, i32 0, i32 1
  %v736 = load i32, i32* %v735
  call void @putint(i32 %v736)
  ret i32 0
if_true_entry559:
  %v614 = alloca i32
  %v615 = call i32 @intpop()
  store i32 %v615, i32* %v614
  %v616 = alloca i32
  %v617 = call i32 @intpop()
  store i32 %v617, i32* %v616
  %v618 = alloca i32
  store i32 zeroinitializer, i32* %v618
  %v623 = load i32, i32* @i22
  %v624 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v623
  %v625 = load i32, i32* %v624
  %bool_627 = icmp eq i32 %v625, 43
  br i1 %bool_627, label %if_true_entry620, label %next_entry622
if_false_entry560:
  %v691 = load i32, i32* @i22
  %v692 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v691
  %v693 = load i32, i32* %v692
  %bool_695 = icmp ne i32 %v693, 32
  br i1 %bool_695, label %if_true_entry688, label %next_entry690
next_entry561:
  %v730 = load i32, i32* @i22
  %v732 = add nsw i32 %v730, 1
  store i32 %v732, i32* @i22
  br i1 %bool_558, label %while_entry550, label %next_entry551
l562:
  br label %while_entry550
r563:
  %v607 = load i32, i32* @i22
  %v608 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v607
  %v609 = load i32, i32* %v608
  %bool_611 = icmp eq i32 %v609, 94
  %bool_613 = icmp ne i1 %bool_611, zeroinitializer
  br i1 %bool_613, label %l562, label %if_false_entry560
l564:
  br label %if_true_entry559
r565:
  %v600 = load i32, i32* @i22
  %v601 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v600
  %v602 = load i32, i32* %v601
  %bool_604 = icmp eq i32 %v602, 37
  %bool_606 = icmp ne i1 %bool_604, zeroinitializer
  br i1 %bool_606, label %l564, label %r563
l566:
  br label %while_entry550
r567:
  %v593 = load i32, i32* @i22
  %v594 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v593
  %v595 = load i32, i32* %v594
  %bool_597 = icmp eq i32 %v595, 47
  %bool_599 = icmp ne i1 %bool_597, zeroinitializer
  br i1 %bool_599, label %l566, label %r565
l568:
  br label %if_true_entry559
r569:
  %v586 = load i32, i32* @i22
  %v587 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v586
  %v588 = load i32, i32* %v587
  %bool_590 = icmp eq i32 %v588, 42
  %bool_592 = icmp ne i1 %bool_590, zeroinitializer
  br i1 %bool_592, label %l568, label %r567
l570:
  br label %while_entry550
r571:
  %v579 = load i32, i32* @i22
  %v580 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v579
  %v581 = load i32, i32* %v580
  %bool_583 = icmp eq i32 %v581, 45
  %bool_585 = icmp ne i1 %bool_583, zeroinitializer
  br i1 %bool_585, label %l570, label %r569
if_true_entry620:
  %v628 = load i32, i32* %v614
  %v629 = load i32, i32* %v616
  %v630 = add nsw i32 %v628, %v629
  store i32 %v630, i32* %v618
  br label %next_entry622
next_entry622:
  %v634 = load i32, i32* @i22
  %v635 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v634
  %v636 = load i32, i32* %v635
  %bool_638 = icmp eq i32 %v636, 45
  br i1 %bool_638, label %if_true_entry631, label %next_entry633
if_true_entry631:
  %v639 = load i32, i32* %v616
  %v640 = load i32, i32* %v614
  %v641 = sub nsw i32 %v639, %v640
  store i32 %v641, i32* %v618
  br label %next_entry633
next_entry633:
  %v645 = load i32, i32* @i22
  %v646 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v645
  %v647 = load i32, i32* %v646
  %bool_649 = icmp eq i32 %v647, 42
  br i1 %bool_649, label %if_true_entry642, label %next_entry644
if_true_entry642:
  %v650 = load i32, i32* %v614
  %v651 = load i32, i32* %v616
  %v652 = mul i32 %v650, %v651
  store i32 %v652, i32* %v618
  br label %next_entry644
next_entry644:
  %v656 = load i32, i32* @i22
  %v657 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v656
  %v658 = load i32, i32* %v657
  %bool_660 = icmp eq i32 %v658, 47
  br i1 %bool_660, label %if_true_entry653, label %next_entry655
if_true_entry653:
  %v661 = load i32, i32* %v616
  %v662 = load i32, i32* %v614
  %v663 = sdiv i32 %v661, %v662
  store i32 %v663, i32* %v618
  br label %next_entry655
next_entry655:
  %v667 = load i32, i32* @i22
  %v668 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v667
  %v669 = load i32, i32* %v668
  %bool_671 = icmp eq i32 %v669, 37
  br i1 %bool_671, label %if_true_entry664, label %next_entry666
if_true_entry664:
  %v672 = load i32, i32* %v616
  %v673 = load i32, i32* %v614
  %v674 = srem i32 %v672, %v673
  store i32 %v674, i32* %v618
  br label %next_entry666
next_entry666:
  %v678 = load i32, i32* @i22
  %v679 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v678
  %v680 = load i32, i32* %v679
  %bool_682 = icmp eq i32 %v680, 94
  br i1 %bool_682, label %if_true_entry675, label %next_entry677
if_true_entry675:
  %v683 = load i32, i32* %v616
  %v684 = load i32, i32* %v614
  %v685 = call i32 @power(i32 %v683, i32 %v684)
  store i32 %v685, i32* %v618
  br label %next_entry677
next_entry677:
  %v686 = load i32, i32* %v618
  call void @intpush(i32 %v686)
  br label %next_entry561
if_true_entry688:
  %v696 = load i32, i32* @i22
  %v697 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v696
  %v698 = load i32, i32* %v697
  %v700 = sub nsw i32 %v698, 48
  call void @intpush(i32 %v700)
  store i32 1, i32* @ii25
  %v705 = load i32, i32* @i22
  %v706 = load i32, i32* @ii25
  %v707 = add nsw i32 %v705, %v706
  %v708 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v707
  %v709 = load i32, i32* %v708
  %bool_711 = icmp ne i32 %v709, 32
  %bool_713 = icmp ne i1 %bool_711, false
  br i1 %bool_713, label %while_entry703, label %next_entry704
next_entry690:
  br label %next_entry561
while_entry703:
  %v714 = load i32, i32* @i22
  %v715 = load i32, i32* @ii25
  %v716 = add nsw i32 %v714, %v715
  %v717 = getelementptr [10000 x i32], [10000 x i32]* @get235, i32 0, i32 %v716
  %v718 = load i32, i32* %v717
  %v720 = sub nsw i32 %v718, 48
  call void @intadd(i32 %v720)
  %v722 = load i32, i32* @ii25
  %v724 = add nsw i32 %v722, 1
  store i32 %v724, i32* @ii25
  br i1 %bool_713, label %while_entry703, label %next_entry704
next_entry704:
  %v725 = load i32, i32* @i22
  %v726 = load i32, i32* @ii25
  %v727 = add nsw i32 %v725, %v726
  %v729 = sub nsw i32 %v727, 1
  store i32 %v729, i32* @i22
  br label %next_entry690
}

