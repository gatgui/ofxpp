/*

Copyright (C) 2010  Gaetan Guidet

This file is part of ofxpp.

ofxpp is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

ofxpp is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

#ifndef __pyofx_macros_h__
#define __pyofx_macros_h__

#define MCR_EXPAND(x) x

#define MCR_CONCAT(x, y) MCR_CONCAT_(x, y)
#define MCR_CONCAT_(x, y) x ## y

#define MCR_STR(x) MCR_STR_(x)
#define MCR_STR_(x) #x

#define MCR_INCR_0 1
#define MCR_INCR_1 2
#define MCR_INCR_2 3
#define MCR_INCR_3 4
#define MCR_INCR_4 5
#define MCR_INCR_5 6
#define MCR_INCR_6 7
#define MCR_INCR_7 8
#define MCR_INCR_8 9
#define MCR_INCR_9 10
#define MCR_INCR_10 11
#define MCR_INCR_11 12
#define MCR_INCR_12 13
#define MCR_INCR_13 14
#define MCR_INCR_14 15
#define MCR_INCR_15 16
#define MCR_INCR_16 17
#define MCR_INCR_17 18
#define MCR_INCR_18 19
#define MCR_INCR_19 20
#define MCR_INCR_20 21
#define MCR_INCR_21 22
#define MCR_INCR_22 23
#define MCR_INCR_23 24
#define MCR_INCR_24 25
#define MCR_INCR_25 26
#define MCR_INCR_26 27
#define MCR_INCR_27 28
#define MCR_INCR_28 29
#define MCR_INCR_29 30
#define MCR_INCR_30 31
#define MCR_INCR_31 32
#define MCR_INCR_32 33
#define MCR_INCR_33 34
#define MCR_INCR_34 35
#define MCR_INCR_35 36
#define MCR_INCR_36 37
#define MCR_INCR_37 38
#define MCR_INCR_38 39
#define MCR_INCR_39 40
#define MCR_INCR_40 41
#define MCR_INCR_41 42
#define MCR_INCR_42 43
#define MCR_INCR_43 44
#define MCR_INCR_44 45
#define MCR_INCR_45 46
#define MCR_INCR_46 47
#define MCR_INCR_47 48
#define MCR_INCR_48 49
#define MCR_INCR_49 50
#define MCR_INCR_50 51
#define MCR_INCR_51 52
#define MCR_INCR_52 53
#define MCR_INCR_53 54
#define MCR_INCR_54 55
#define MCR_INCR_55 56
#define MCR_INCR_56 57
#define MCR_INCR_57 58
#define MCR_INCR_58 59
#define MCR_INCR_59 60
#define MCR_INCR_60 61
#define MCR_INCR_61 62
#define MCR_INCR_62 63
#define MCR_INCR_63 64
#define MCR_INCR_64 65
#define MCR_INCR_65 66
#define MCR_INCR_66 67
#define MCR_INCR_67 68
#define MCR_INCR_68 69
#define MCR_INCR_69 70
#define MCR_INCR_70 71
#define MCR_INCR_71 72
#define MCR_INCR_72 73
#define MCR_INCR_73 74
#define MCR_INCR_74 75
#define MCR_INCR_75 76
#define MCR_INCR_76 77
#define MCR_INCR_77 78
#define MCR_INCR_78 79
#define MCR_INCR_79 80
#define MCR_INCR_80 81
#define MCR_INCR_81 82
#define MCR_INCR_82 83
#define MCR_INCR_83 84
#define MCR_INCR_84 85
#define MCR_INCR_85 86
#define MCR_INCR_86 87
#define MCR_INCR_87 88
#define MCR_INCR_88 89
#define MCR_INCR_89 90
#define MCR_INCR_90 91
#define MCR_INCR_91 92
#define MCR_INCR_92 93
#define MCR_INCR_93 94
#define MCR_INCR_94 95
#define MCR_INCR_95 96
#define MCR_INCR_96 97
#define MCR_INCR_97 98
#define MCR_INCR_98 99
#define MCR_INCR_99 100
#define MCR_INCR_100 101
#define MCR_INCR_101 102
#define MCR_INCR_102 103
#define MCR_INCR_103 104
#define MCR_INCR_104 105
#define MCR_INCR_105 106
#define MCR_INCR_106 107
#define MCR_INCR_107 108
#define MCR_INCR_108 109
#define MCR_INCR_109 110
#define MCR_INCR_110 111
#define MCR_INCR_111 112
#define MCR_INCR_112 113
#define MCR_INCR_113 114
#define MCR_INCR_114 115
#define MCR_INCR_115 116
#define MCR_INCR_116 117
#define MCR_INCR_117 118
#define MCR_INCR_118 119
#define MCR_INCR_119 120
#define MCR_INCR_120 121
#define MCR_INCR_121 122
#define MCR_INCR_122 123
#define MCR_INCR_123 124
#define MCR_INCR_124 125
#define MCR_INCR_125 126
#define MCR_INCR_126 127
#define MCR_INCR_127 128
#define MCR_INCR_128 129
#define MCR_INCR_129 130
#define MCR_INCR_130 131
#define MCR_INCR_131 132
#define MCR_INCR_132 133
#define MCR_INCR_133 134
#define MCR_INCR_134 135
#define MCR_INCR_135 136
#define MCR_INCR_136 137
#define MCR_INCR_137 138
#define MCR_INCR_138 139
#define MCR_INCR_139 140
#define MCR_INCR_140 141
#define MCR_INCR_141 142
#define MCR_INCR_142 143
#define MCR_INCR_143 144
#define MCR_INCR_144 145
#define MCR_INCR_145 146
#define MCR_INCR_146 147
#define MCR_INCR_147 148
#define MCR_INCR_148 149
#define MCR_INCR_149 150
#define MCR_INCR_150 151
#define MCR_INCR_151 152
#define MCR_INCR_152 153
#define MCR_INCR_153 154
#define MCR_INCR_154 155
#define MCR_INCR_155 156
#define MCR_INCR_156 157
#define MCR_INCR_157 158
#define MCR_INCR_158 159
#define MCR_INCR_159 160
#define MCR_INCR_160 161
#define MCR_INCR_161 162
#define MCR_INCR_162 163
#define MCR_INCR_163 164
#define MCR_INCR_164 165
#define MCR_INCR_165 166
#define MCR_INCR_166 167
#define MCR_INCR_167 168
#define MCR_INCR_168 169
#define MCR_INCR_169 170
#define MCR_INCR_170 171
#define MCR_INCR_171 172
#define MCR_INCR_172 173
#define MCR_INCR_173 174
#define MCR_INCR_174 175
#define MCR_INCR_175 176
#define MCR_INCR_176 177
#define MCR_INCR_177 178
#define MCR_INCR_178 179
#define MCR_INCR_179 180
#define MCR_INCR_180 181
#define MCR_INCR_181 182
#define MCR_INCR_182 183
#define MCR_INCR_183 184
#define MCR_INCR_184 185
#define MCR_INCR_185 186
#define MCR_INCR_186 187
#define MCR_INCR_187 188
#define MCR_INCR_188 189
#define MCR_INCR_189 190
#define MCR_INCR_190 191
#define MCR_INCR_191 192
#define MCR_INCR_192 193
#define MCR_INCR_193 194
#define MCR_INCR_194 195
#define MCR_INCR_195 196
#define MCR_INCR_196 197
#define MCR_INCR_197 198
#define MCR_INCR_198 199
#define MCR_INCR_199 200
#define MCR_INCR_200 201
#define MCR_INCR_201 202
#define MCR_INCR_202 203
#define MCR_INCR_203 204
#define MCR_INCR_204 205
#define MCR_INCR_205 206
#define MCR_INCR_206 207
#define MCR_INCR_207 208
#define MCR_INCR_208 209
#define MCR_INCR_209 210
#define MCR_INCR_210 211
#define MCR_INCR_211 212
#define MCR_INCR_212 213
#define MCR_INCR_213 214
#define MCR_INCR_214 215
#define MCR_INCR_215 216
#define MCR_INCR_216 217
#define MCR_INCR_217 218
#define MCR_INCR_218 219
#define MCR_INCR_219 220
#define MCR_INCR_220 221
#define MCR_INCR_221 222
#define MCR_INCR_222 223
#define MCR_INCR_223 224
#define MCR_INCR_224 225
#define MCR_INCR_225 226
#define MCR_INCR_226 227
#define MCR_INCR_227 228
#define MCR_INCR_228 229
#define MCR_INCR_229 230
#define MCR_INCR_230 231
#define MCR_INCR_231 232
#define MCR_INCR_232 233
#define MCR_INCR_233 234
#define MCR_INCR_234 235
#define MCR_INCR_235 236
#define MCR_INCR_236 237
#define MCR_INCR_237 238
#define MCR_INCR_238 239
#define MCR_INCR_239 240
#define MCR_INCR_240 241
#define MCR_INCR_241 242
#define MCR_INCR_242 243
#define MCR_INCR_243 244
#define MCR_INCR_244 245
#define MCR_INCR_245 246
#define MCR_INCR_246 247
#define MCR_INCR_247 248
#define MCR_INCR_248 249
#define MCR_INCR_249 250
#define MCR_INCR_250 251
#define MCR_INCR_251 252
#define MCR_INCR_252 253
#define MCR_INCR_253 254
#define MCR_INCR_254 255
#define MCR_INCR_255 256
#define MCR_INCR_256 257
#define MCR_INCR_257 258
#define MCR_INCR_258 259
#define MCR_INCR_259 260
#define MCR_INCR_260 261
#define MCR_INCR_261 262
#define MCR_INCR_262 263
#define MCR_INCR_263 264
#define MCR_INCR_264 265
#define MCR_INCR_265 266
#define MCR_INCR_266 267
#define MCR_INCR_267 268
#define MCR_INCR_268 269
#define MCR_INCR_269 270
#define MCR_INCR_270 271
#define MCR_INCR_271 272
#define MCR_INCR_272 273
#define MCR_INCR_273 274
#define MCR_INCR_274 275
#define MCR_INCR_275 276
#define MCR_INCR_276 277
#define MCR_INCR_277 278
#define MCR_INCR_278 279
#define MCR_INCR_279 280
#define MCR_INCR_280 281
#define MCR_INCR_281 282
#define MCR_INCR_282 283
#define MCR_INCR_283 284
#define MCR_INCR_284 285
#define MCR_INCR_285 286
#define MCR_INCR_286 287
#define MCR_INCR_287 288
#define MCR_INCR_288 289
#define MCR_INCR_289 290
#define MCR_INCR_290 291
#define MCR_INCR_291 292
#define MCR_INCR_292 293
#define MCR_INCR_293 294
#define MCR_INCR_294 295
#define MCR_INCR_295 296
#define MCR_INCR_296 297
#define MCR_INCR_297 298
#define MCR_INCR_298 299
#define MCR_INCR_299 300
#define MCR_INCR_300 301
#define MCR_INCR_301 302
#define MCR_INCR_302 303
#define MCR_INCR_303 304
#define MCR_INCR_304 305
#define MCR_INCR_305 306
#define MCR_INCR_306 307
#define MCR_INCR_307 308
#define MCR_INCR_308 309
#define MCR_INCR_309 310
#define MCR_INCR_310 311
#define MCR_INCR_311 312
#define MCR_INCR_312 313
#define MCR_INCR_313 314
#define MCR_INCR_314 315
#define MCR_INCR_315 316
#define MCR_INCR_316 317
#define MCR_INCR_317 318
#define MCR_INCR_318 319
#define MCR_INCR_319 320
#define MCR_INCR_320 321
#define MCR_INCR_321 322
#define MCR_INCR_322 323
#define MCR_INCR_323 324
#define MCR_INCR_324 325
#define MCR_INCR_325 326
#define MCR_INCR_326 327
#define MCR_INCR_327 328
#define MCR_INCR_328 329
#define MCR_INCR_329 330
#define MCR_INCR_330 331
#define MCR_INCR_331 332
#define MCR_INCR_332 333
#define MCR_INCR_333 334
#define MCR_INCR_334 335
#define MCR_INCR_335 336
#define MCR_INCR_336 337
#define MCR_INCR_337 338
#define MCR_INCR_338 339
#define MCR_INCR_339 340
#define MCR_INCR_340 341
#define MCR_INCR_341 342
#define MCR_INCR_342 343
#define MCR_INCR_343 344
#define MCR_INCR_344 345
#define MCR_INCR_345 346
#define MCR_INCR_346 347
#define MCR_INCR_347 348
#define MCR_INCR_348 349
#define MCR_INCR_349 350
#define MCR_INCR_350 351
#define MCR_INCR_351 352
#define MCR_INCR_352 353
#define MCR_INCR_353 354
#define MCR_INCR_354 355
#define MCR_INCR_355 356
#define MCR_INCR_356 357
#define MCR_INCR_357 358
#define MCR_INCR_358 359
#define MCR_INCR_359 360
#define MCR_INCR_360 361
#define MCR_INCR_361 362
#define MCR_INCR_362 363
#define MCR_INCR_363 364
#define MCR_INCR_364 365
#define MCR_INCR_365 366
#define MCR_INCR_366 367
#define MCR_INCR_367 368
#define MCR_INCR_368 369
#define MCR_INCR_369 370
#define MCR_INCR_370 371
#define MCR_INCR_371 372
#define MCR_INCR_372 373
#define MCR_INCR_373 374
#define MCR_INCR_374 375
#define MCR_INCR_375 376
#define MCR_INCR_376 377
#define MCR_INCR_377 378
#define MCR_INCR_378 379
#define MCR_INCR_379 380
#define MCR_INCR_380 381
#define MCR_INCR_381 382
#define MCR_INCR_382 383
#define MCR_INCR_383 384
#define MCR_INCR_384 385
#define MCR_INCR_385 386
#define MCR_INCR_386 387
#define MCR_INCR_387 388
#define MCR_INCR_388 389
#define MCR_INCR_389 390
#define MCR_INCR_390 391
#define MCR_INCR_391 392
#define MCR_INCR_392 393
#define MCR_INCR_393 394
#define MCR_INCR_394 395
#define MCR_INCR_395 396
#define MCR_INCR_396 397
#define MCR_INCR_397 398
#define MCR_INCR_398 399
#define MCR_INCR_399 400
#define MCR_INCR_400 401
#define MCR_INCR_401 402
#define MCR_INCR_402 403
#define MCR_INCR_403 404
#define MCR_INCR_404 405
#define MCR_INCR_405 406
#define MCR_INCR_406 407
#define MCR_INCR_407 408
#define MCR_INCR_408 409
#define MCR_INCR_409 410
#define MCR_INCR_410 411
#define MCR_INCR_411 412
#define MCR_INCR_412 413
#define MCR_INCR_413 414
#define MCR_INCR_414 415
#define MCR_INCR_415 416
#define MCR_INCR_416 417
#define MCR_INCR_417 418
#define MCR_INCR_418 419
#define MCR_INCR_419 420
#define MCR_INCR_420 421
#define MCR_INCR_421 422
#define MCR_INCR_422 423
#define MCR_INCR_423 424
#define MCR_INCR_424 425
#define MCR_INCR_425 426
#define MCR_INCR_426 427
#define MCR_INCR_427 428
#define MCR_INCR_428 429
#define MCR_INCR_429 430
#define MCR_INCR_430 431
#define MCR_INCR_431 432
#define MCR_INCR_432 433
#define MCR_INCR_433 434
#define MCR_INCR_434 435
#define MCR_INCR_435 436
#define MCR_INCR_436 437
#define MCR_INCR_437 438
#define MCR_INCR_438 439
#define MCR_INCR_439 440
#define MCR_INCR_440 441
#define MCR_INCR_441 442
#define MCR_INCR_442 443
#define MCR_INCR_443 444
#define MCR_INCR_444 445
#define MCR_INCR_445 446
#define MCR_INCR_446 447
#define MCR_INCR_447 448
#define MCR_INCR_448 449
#define MCR_INCR_449 450
#define MCR_INCR_450 451
#define MCR_INCR_451 452
#define MCR_INCR_452 453
#define MCR_INCR_453 454
#define MCR_INCR_454 455
#define MCR_INCR_455 456
#define MCR_INCR_456 457
#define MCR_INCR_457 458
#define MCR_INCR_458 459
#define MCR_INCR_459 460
#define MCR_INCR_460 461
#define MCR_INCR_461 462
#define MCR_INCR_462 463
#define MCR_INCR_463 464
#define MCR_INCR_464 465
#define MCR_INCR_465 466
#define MCR_INCR_466 467
#define MCR_INCR_467 468
#define MCR_INCR_468 469
#define MCR_INCR_469 470
#define MCR_INCR_470 471
#define MCR_INCR_471 472
#define MCR_INCR_472 473
#define MCR_INCR_473 474
#define MCR_INCR_474 475
#define MCR_INCR_475 476
#define MCR_INCR_476 477
#define MCR_INCR_477 478
#define MCR_INCR_478 479
#define MCR_INCR_479 480
#define MCR_INCR_480 481
#define MCR_INCR_481 482
#define MCR_INCR_482 483
#define MCR_INCR_483 484
#define MCR_INCR_484 485
#define MCR_INCR_485 486
#define MCR_INCR_486 487
#define MCR_INCR_487 488
#define MCR_INCR_488 489
#define MCR_INCR_489 490
#define MCR_INCR_490 491
#define MCR_INCR_491 492
#define MCR_INCR_492 493
#define MCR_INCR_493 494
#define MCR_INCR_494 495
#define MCR_INCR_495 496
#define MCR_INCR_496 497
#define MCR_INCR_497 498
#define MCR_INCR_498 499
#define MCR_INCR_499 500
#define MCR_INCR_500 501
#define MCR_INCR_501 502
#define MCR_INCR_502 503
#define MCR_INCR_503 504
#define MCR_INCR_504 505
#define MCR_INCR_505 506
#define MCR_INCR_506 507
#define MCR_INCR_507 508
#define MCR_INCR_508 509
#define MCR_INCR_509 510
#define MCR_INCR_510 511
#define MCR_INCR_511 512
#define MCR_INCR_512 513
#define MCR_INCR(n) MCR_CONCAT(MCR_INCR_, n)

#define MCR_DECR_0 
#define MCR_DECR_1 0
#define MCR_DECR_2 1
#define MCR_DECR_3 2
#define MCR_DECR_4 3
#define MCR_DECR_5 4
#define MCR_DECR_6 5
#define MCR_DECR_7 6
#define MCR_DECR_8 7
#define MCR_DECR_9 8
#define MCR_DECR_10 9
#define MCR_DECR_11 10
#define MCR_DECR_12 11
#define MCR_DECR_13 12
#define MCR_DECR_14 13
#define MCR_DECR_15 14
#define MCR_DECR_16 15
#define MCR_DECR_17 16
#define MCR_DECR_18 17
#define MCR_DECR_19 18
#define MCR_DECR_20 19
#define MCR_DECR_21 20
#define MCR_DECR_22 21
#define MCR_DECR_23 22
#define MCR_DECR_24 23
#define MCR_DECR_25 24
#define MCR_DECR_26 25
#define MCR_DECR_27 26
#define MCR_DECR_28 27
#define MCR_DECR_29 28
#define MCR_DECR_30 29
#define MCR_DECR_31 30
#define MCR_DECR_32 31
#define MCR_DECR_33 32
#define MCR_DECR_34 33
#define MCR_DECR_35 34
#define MCR_DECR_36 35
#define MCR_DECR_37 36
#define MCR_DECR_38 37
#define MCR_DECR_39 38
#define MCR_DECR_40 39
#define MCR_DECR_41 40
#define MCR_DECR_42 41
#define MCR_DECR_43 42
#define MCR_DECR_44 43
#define MCR_DECR_45 44
#define MCR_DECR_46 45
#define MCR_DECR_47 46
#define MCR_DECR_48 47
#define MCR_DECR_49 48
#define MCR_DECR_50 49
#define MCR_DECR_51 50
#define MCR_DECR_52 51
#define MCR_DECR_53 52
#define MCR_DECR_54 53
#define MCR_DECR_55 54
#define MCR_DECR_56 55
#define MCR_DECR_57 56
#define MCR_DECR_58 57
#define MCR_DECR_59 58
#define MCR_DECR_60 59
#define MCR_DECR_61 60
#define MCR_DECR_62 61
#define MCR_DECR_63 62
#define MCR_DECR_64 63
#define MCR_DECR_65 64
#define MCR_DECR_66 65
#define MCR_DECR_67 66
#define MCR_DECR_68 67
#define MCR_DECR_69 68
#define MCR_DECR_70 69
#define MCR_DECR_71 70
#define MCR_DECR_72 71
#define MCR_DECR_73 72
#define MCR_DECR_74 73
#define MCR_DECR_75 74
#define MCR_DECR_76 75
#define MCR_DECR_77 76
#define MCR_DECR_78 77
#define MCR_DECR_79 78
#define MCR_DECR_80 79
#define MCR_DECR_81 80
#define MCR_DECR_82 81
#define MCR_DECR_83 82
#define MCR_DECR_84 83
#define MCR_DECR_85 84
#define MCR_DECR_86 85
#define MCR_DECR_87 86
#define MCR_DECR_88 87
#define MCR_DECR_89 88
#define MCR_DECR_90 89
#define MCR_DECR_91 90
#define MCR_DECR_92 91
#define MCR_DECR_93 92
#define MCR_DECR_94 93
#define MCR_DECR_95 94
#define MCR_DECR_96 95
#define MCR_DECR_97 96
#define MCR_DECR_98 97
#define MCR_DECR_99 98
#define MCR_DECR_100 99
#define MCR_DECR_101 100
#define MCR_DECR_102 101
#define MCR_DECR_103 102
#define MCR_DECR_104 103
#define MCR_DECR_105 104
#define MCR_DECR_106 105
#define MCR_DECR_107 106
#define MCR_DECR_108 107
#define MCR_DECR_109 108
#define MCR_DECR_110 109
#define MCR_DECR_111 110
#define MCR_DECR_112 111
#define MCR_DECR_113 112
#define MCR_DECR_114 113
#define MCR_DECR_115 114
#define MCR_DECR_116 115
#define MCR_DECR_117 116
#define MCR_DECR_118 117
#define MCR_DECR_119 118
#define MCR_DECR_120 119
#define MCR_DECR_121 120
#define MCR_DECR_122 121
#define MCR_DECR_123 122
#define MCR_DECR_124 123
#define MCR_DECR_125 124
#define MCR_DECR_126 125
#define MCR_DECR_127 126
#define MCR_DECR_128 127
#define MCR_DECR_129 128
#define MCR_DECR_130 129
#define MCR_DECR_131 130
#define MCR_DECR_132 131
#define MCR_DECR_133 132
#define MCR_DECR_134 133
#define MCR_DECR_135 134
#define MCR_DECR_136 135
#define MCR_DECR_137 136
#define MCR_DECR_138 137
#define MCR_DECR_139 138
#define MCR_DECR_140 139
#define MCR_DECR_141 140
#define MCR_DECR_142 141
#define MCR_DECR_143 142
#define MCR_DECR_144 143
#define MCR_DECR_145 144
#define MCR_DECR_146 145
#define MCR_DECR_147 146
#define MCR_DECR_148 147
#define MCR_DECR_149 148
#define MCR_DECR_150 149
#define MCR_DECR_151 150
#define MCR_DECR_152 151
#define MCR_DECR_153 152
#define MCR_DECR_154 153
#define MCR_DECR_155 154
#define MCR_DECR_156 155
#define MCR_DECR_157 156
#define MCR_DECR_158 157
#define MCR_DECR_159 158
#define MCR_DECR_160 159
#define MCR_DECR_161 160
#define MCR_DECR_162 161
#define MCR_DECR_163 162
#define MCR_DECR_164 163
#define MCR_DECR_165 164
#define MCR_DECR_166 165
#define MCR_DECR_167 166
#define MCR_DECR_168 167
#define MCR_DECR_169 168
#define MCR_DECR_170 169
#define MCR_DECR_171 170
#define MCR_DECR_172 171
#define MCR_DECR_173 172
#define MCR_DECR_174 173
#define MCR_DECR_175 174
#define MCR_DECR_176 175
#define MCR_DECR_177 176
#define MCR_DECR_178 177
#define MCR_DECR_179 178
#define MCR_DECR_180 179
#define MCR_DECR_181 180
#define MCR_DECR_182 181
#define MCR_DECR_183 182
#define MCR_DECR_184 183
#define MCR_DECR_185 184
#define MCR_DECR_186 185
#define MCR_DECR_187 186
#define MCR_DECR_188 187
#define MCR_DECR_189 188
#define MCR_DECR_190 189
#define MCR_DECR_191 190
#define MCR_DECR_192 191
#define MCR_DECR_193 192
#define MCR_DECR_194 193
#define MCR_DECR_195 194
#define MCR_DECR_196 195
#define MCR_DECR_197 196
#define MCR_DECR_198 197
#define MCR_DECR_199 198
#define MCR_DECR_200 199
#define MCR_DECR_201 200
#define MCR_DECR_202 201
#define MCR_DECR_203 202
#define MCR_DECR_204 203
#define MCR_DECR_205 204
#define MCR_DECR_206 205
#define MCR_DECR_207 206
#define MCR_DECR_208 207
#define MCR_DECR_209 208
#define MCR_DECR_210 209
#define MCR_DECR_211 210
#define MCR_DECR_212 211
#define MCR_DECR_213 212
#define MCR_DECR_214 213
#define MCR_DECR_215 214
#define MCR_DECR_216 215
#define MCR_DECR_217 216
#define MCR_DECR_218 217
#define MCR_DECR_219 218
#define MCR_DECR_220 219
#define MCR_DECR_221 220
#define MCR_DECR_222 221
#define MCR_DECR_223 222
#define MCR_DECR_224 223
#define MCR_DECR_225 224
#define MCR_DECR_226 225
#define MCR_DECR_227 226
#define MCR_DECR_228 227
#define MCR_DECR_229 228
#define MCR_DECR_230 229
#define MCR_DECR_231 230
#define MCR_DECR_232 231
#define MCR_DECR_233 232
#define MCR_DECR_234 233
#define MCR_DECR_235 234
#define MCR_DECR_236 235
#define MCR_DECR_237 236
#define MCR_DECR_238 237
#define MCR_DECR_239 238
#define MCR_DECR_240 239
#define MCR_DECR_241 240
#define MCR_DECR_242 241
#define MCR_DECR_243 242
#define MCR_DECR_244 243
#define MCR_DECR_245 244
#define MCR_DECR_246 245
#define MCR_DECR_247 246
#define MCR_DECR_248 247
#define MCR_DECR_249 248
#define MCR_DECR_250 249
#define MCR_DECR_251 250
#define MCR_DECR_252 251
#define MCR_DECR_253 252
#define MCR_DECR_254 253
#define MCR_DECR_255 254
#define MCR_DECR_256 255
#define MCR_DECR_257 256
#define MCR_DECR_258 257
#define MCR_DECR_259 258
#define MCR_DECR_260 259
#define MCR_DECR_261 260
#define MCR_DECR_262 261
#define MCR_DECR_263 262
#define MCR_DECR_264 263
#define MCR_DECR_265 264
#define MCR_DECR_266 265
#define MCR_DECR_267 266
#define MCR_DECR_268 267
#define MCR_DECR_269 268
#define MCR_DECR_270 269
#define MCR_DECR_271 270
#define MCR_DECR_272 271
#define MCR_DECR_273 272
#define MCR_DECR_274 273
#define MCR_DECR_275 274
#define MCR_DECR_276 275
#define MCR_DECR_277 276
#define MCR_DECR_278 277
#define MCR_DECR_279 278
#define MCR_DECR_280 279
#define MCR_DECR_281 280
#define MCR_DECR_282 281
#define MCR_DECR_283 282
#define MCR_DECR_284 283
#define MCR_DECR_285 284
#define MCR_DECR_286 285
#define MCR_DECR_287 286
#define MCR_DECR_288 287
#define MCR_DECR_289 288
#define MCR_DECR_290 289
#define MCR_DECR_291 290
#define MCR_DECR_292 291
#define MCR_DECR_293 292
#define MCR_DECR_294 293
#define MCR_DECR_295 294
#define MCR_DECR_296 295
#define MCR_DECR_297 296
#define MCR_DECR_298 297
#define MCR_DECR_299 298
#define MCR_DECR_300 299
#define MCR_DECR_301 300
#define MCR_DECR_302 301
#define MCR_DECR_303 302
#define MCR_DECR_304 303
#define MCR_DECR_305 304
#define MCR_DECR_306 305
#define MCR_DECR_307 306
#define MCR_DECR_308 307
#define MCR_DECR_309 308
#define MCR_DECR_310 309
#define MCR_DECR_311 310
#define MCR_DECR_312 311
#define MCR_DECR_313 312
#define MCR_DECR_314 313
#define MCR_DECR_315 314
#define MCR_DECR_316 315
#define MCR_DECR_317 316
#define MCR_DECR_318 317
#define MCR_DECR_319 318
#define MCR_DECR_320 319
#define MCR_DECR_321 320
#define MCR_DECR_322 321
#define MCR_DECR_323 322
#define MCR_DECR_324 323
#define MCR_DECR_325 324
#define MCR_DECR_326 325
#define MCR_DECR_327 326
#define MCR_DECR_328 327
#define MCR_DECR_329 328
#define MCR_DECR_330 329
#define MCR_DECR_331 330
#define MCR_DECR_332 331
#define MCR_DECR_333 332
#define MCR_DECR_334 333
#define MCR_DECR_335 334
#define MCR_DECR_336 335
#define MCR_DECR_337 336
#define MCR_DECR_338 337
#define MCR_DECR_339 338
#define MCR_DECR_340 339
#define MCR_DECR_341 340
#define MCR_DECR_342 341
#define MCR_DECR_343 342
#define MCR_DECR_344 343
#define MCR_DECR_345 344
#define MCR_DECR_346 345
#define MCR_DECR_347 346
#define MCR_DECR_348 347
#define MCR_DECR_349 348
#define MCR_DECR_350 349
#define MCR_DECR_351 350
#define MCR_DECR_352 351
#define MCR_DECR_353 352
#define MCR_DECR_354 353
#define MCR_DECR_355 354
#define MCR_DECR_356 355
#define MCR_DECR_357 356
#define MCR_DECR_358 357
#define MCR_DECR_359 358
#define MCR_DECR_360 359
#define MCR_DECR_361 360
#define MCR_DECR_362 361
#define MCR_DECR_363 362
#define MCR_DECR_364 363
#define MCR_DECR_365 364
#define MCR_DECR_366 365
#define MCR_DECR_367 366
#define MCR_DECR_368 367
#define MCR_DECR_369 368
#define MCR_DECR_370 369
#define MCR_DECR_371 370
#define MCR_DECR_372 371
#define MCR_DECR_373 372
#define MCR_DECR_374 373
#define MCR_DECR_375 374
#define MCR_DECR_376 375
#define MCR_DECR_377 376
#define MCR_DECR_378 377
#define MCR_DECR_379 378
#define MCR_DECR_380 379
#define MCR_DECR_381 380
#define MCR_DECR_382 381
#define MCR_DECR_383 382
#define MCR_DECR_384 383
#define MCR_DECR_385 384
#define MCR_DECR_386 385
#define MCR_DECR_387 386
#define MCR_DECR_388 387
#define MCR_DECR_389 388
#define MCR_DECR_390 389
#define MCR_DECR_391 390
#define MCR_DECR_392 391
#define MCR_DECR_393 392
#define MCR_DECR_394 393
#define MCR_DECR_395 394
#define MCR_DECR_396 395
#define MCR_DECR_397 396
#define MCR_DECR_398 397
#define MCR_DECR_399 398
#define MCR_DECR_400 399
#define MCR_DECR_401 400
#define MCR_DECR_402 401
#define MCR_DECR_403 402
#define MCR_DECR_404 403
#define MCR_DECR_405 404
#define MCR_DECR_406 405
#define MCR_DECR_407 406
#define MCR_DECR_408 407
#define MCR_DECR_409 408
#define MCR_DECR_410 409
#define MCR_DECR_411 410
#define MCR_DECR_412 411
#define MCR_DECR_413 412
#define MCR_DECR_414 413
#define MCR_DECR_415 414
#define MCR_DECR_416 415
#define MCR_DECR_417 416
#define MCR_DECR_418 417
#define MCR_DECR_419 418
#define MCR_DECR_420 419
#define MCR_DECR_421 420
#define MCR_DECR_422 421
#define MCR_DECR_423 422
#define MCR_DECR_424 423
#define MCR_DECR_425 424
#define MCR_DECR_426 425
#define MCR_DECR_427 426
#define MCR_DECR_428 427
#define MCR_DECR_429 428
#define MCR_DECR_430 429
#define MCR_DECR_431 430
#define MCR_DECR_432 431
#define MCR_DECR_433 432
#define MCR_DECR_434 433
#define MCR_DECR_435 434
#define MCR_DECR_436 435
#define MCR_DECR_437 436
#define MCR_DECR_438 437
#define MCR_DECR_439 438
#define MCR_DECR_440 439
#define MCR_DECR_441 440
#define MCR_DECR_442 441
#define MCR_DECR_443 442
#define MCR_DECR_444 443
#define MCR_DECR_445 444
#define MCR_DECR_446 445
#define MCR_DECR_447 446
#define MCR_DECR_448 447
#define MCR_DECR_449 448
#define MCR_DECR_450 449
#define MCR_DECR_451 450
#define MCR_DECR_452 451
#define MCR_DECR_453 452
#define MCR_DECR_454 453
#define MCR_DECR_455 454
#define MCR_DECR_456 455
#define MCR_DECR_457 456
#define MCR_DECR_458 457
#define MCR_DECR_459 458
#define MCR_DECR_460 459
#define MCR_DECR_461 460
#define MCR_DECR_462 461
#define MCR_DECR_463 462
#define MCR_DECR_464 463
#define MCR_DECR_465 464
#define MCR_DECR_466 465
#define MCR_DECR_467 466
#define MCR_DECR_468 467
#define MCR_DECR_469 468
#define MCR_DECR_470 469
#define MCR_DECR_471 470
#define MCR_DECR_472 471
#define MCR_DECR_473 472
#define MCR_DECR_474 473
#define MCR_DECR_475 474
#define MCR_DECR_476 475
#define MCR_DECR_477 476
#define MCR_DECR_478 477
#define MCR_DECR_479 478
#define MCR_DECR_480 479
#define MCR_DECR_481 480
#define MCR_DECR_482 481
#define MCR_DECR_483 482
#define MCR_DECR_484 483
#define MCR_DECR_485 484
#define MCR_DECR_486 485
#define MCR_DECR_487 486
#define MCR_DECR_488 487
#define MCR_DECR_489 488
#define MCR_DECR_490 489
#define MCR_DECR_491 490
#define MCR_DECR_492 491
#define MCR_DECR_493 492
#define MCR_DECR_494 493
#define MCR_DECR_495 494
#define MCR_DECR_496 495
#define MCR_DECR_497 496
#define MCR_DECR_498 497
#define MCR_DECR_499 498
#define MCR_DECR_500 499
#define MCR_DECR_501 500
#define MCR_DECR_502 501
#define MCR_DECR_503 502
#define MCR_DECR_504 503
#define MCR_DECR_505 504
#define MCR_DECR_506 505
#define MCR_DECR_507 506
#define MCR_DECR_508 507
#define MCR_DECR_509 508
#define MCR_DECR_510 509
#define MCR_DECR_511 510
#define MCR_DECR_512 511
#define MCR_DECR(n) MCR_CONCAT(MCR_DECR_, n)

#define MCR_REP_0(macro, p0, p1, p2) 
#define MCR_REP_1(macro, p0, p1, p2) MCR_REP_0(macro, p0, p1, p2) macro(1, p0, p1, p2)
#define MCR_REP_2(macro, p0, p1, p2) MCR_REP_1(macro, p0, p1, p2) macro(2, p0, p1, p2)
#define MCR_REP_3(macro, p0, p1, p2) MCR_REP_2(macro, p0, p1, p2) macro(3, p0, p1, p2)
#define MCR_REP_4(macro, p0, p1, p2) MCR_REP_3(macro, p0, p1, p2) macro(4, p0, p1, p2)
#define MCR_REP_5(macro, p0, p1, p2) MCR_REP_4(macro, p0, p1, p2) macro(5, p0, p1, p2)
#define MCR_REP_6(macro, p0, p1, p2) MCR_REP_5(macro, p0, p1, p2) macro(6, p0, p1, p2)
#define MCR_REP_7(macro, p0, p1, p2) MCR_REP_6(macro, p0, p1, p2) macro(7, p0, p1, p2)
#define MCR_REP_8(macro, p0, p1, p2) MCR_REP_7(macro, p0, p1, p2) macro(8, p0, p1, p2)
#define MCR_REP_9(macro, p0, p1, p2) MCR_REP_8(macro, p0, p1, p2) macro(9, p0, p1, p2)
#define MCR_REP_10(macro, p0, p1, p2) MCR_REP_9(macro, p0, p1, p2) macro(10, p0, p1, p2)
#define MCR_REP_11(macro, p0, p1, p2) MCR_REP_10(macro, p0, p1, p2) macro(11, p0, p1, p2)
#define MCR_REP_12(macro, p0, p1, p2) MCR_REP_11(macro, p0, p1, p2) macro(12, p0, p1, p2)
#define MCR_REP_13(macro, p0, p1, p2) MCR_REP_12(macro, p0, p1, p2) macro(13, p0, p1, p2)
#define MCR_REP_14(macro, p0, p1, p2) MCR_REP_13(macro, p0, p1, p2) macro(14, p0, p1, p2)
#define MCR_REP_15(macro, p0, p1, p2) MCR_REP_14(macro, p0, p1, p2) macro(15, p0, p1, p2)
#define MCR_REP_16(macro, p0, p1, p2) MCR_REP_15(macro, p0, p1, p2) macro(16, p0, p1, p2)
#define MCR_REP_17(macro, p0, p1, p2) MCR_REP_16(macro, p0, p1, p2) macro(17, p0, p1, p2)
#define MCR_REP_18(macro, p0, p1, p2) MCR_REP_17(macro, p0, p1, p2) macro(18, p0, p1, p2)
#define MCR_REP_19(macro, p0, p1, p2) MCR_REP_18(macro, p0, p1, p2) macro(19, p0, p1, p2)
#define MCR_REP_20(macro, p0, p1, p2) MCR_REP_19(macro, p0, p1, p2) macro(20, p0, p1, p2)
#define MCR_REP_21(macro, p0, p1, p2) MCR_REP_20(macro, p0, p1, p2) macro(21, p0, p1, p2)
#define MCR_REP_22(macro, p0, p1, p2) MCR_REP_21(macro, p0, p1, p2) macro(22, p0, p1, p2)
#define MCR_REP_23(macro, p0, p1, p2) MCR_REP_22(macro, p0, p1, p2) macro(23, p0, p1, p2)
#define MCR_REP_24(macro, p0, p1, p2) MCR_REP_23(macro, p0, p1, p2) macro(24, p0, p1, p2)
#define MCR_REP_25(macro, p0, p1, p2) MCR_REP_24(macro, p0, p1, p2) macro(25, p0, p1, p2)
#define MCR_REP_26(macro, p0, p1, p2) MCR_REP_25(macro, p0, p1, p2) macro(26, p0, p1, p2)
#define MCR_REP_27(macro, p0, p1, p2) MCR_REP_26(macro, p0, p1, p2) macro(27, p0, p1, p2)
#define MCR_REP_28(macro, p0, p1, p2) MCR_REP_27(macro, p0, p1, p2) macro(28, p0, p1, p2)
#define MCR_REP_29(macro, p0, p1, p2) MCR_REP_28(macro, p0, p1, p2) macro(29, p0, p1, p2)
#define MCR_REP_30(macro, p0, p1, p2) MCR_REP_29(macro, p0, p1, p2) macro(30, p0, p1, p2)
#define MCR_REP_31(macro, p0, p1, p2) MCR_REP_30(macro, p0, p1, p2) macro(31, p0, p1, p2)
#define MCR_REP_32(macro, p0, p1, p2) MCR_REP_31(macro, p0, p1, p2) macro(32, p0, p1, p2)
#define MCR_REP_33(macro, p0, p1, p2) MCR_REP_32(macro, p0, p1, p2) macro(33, p0, p1, p2)
#define MCR_REP_34(macro, p0, p1, p2) MCR_REP_33(macro, p0, p1, p2) macro(34, p0, p1, p2)
#define MCR_REP_35(macro, p0, p1, p2) MCR_REP_34(macro, p0, p1, p2) macro(35, p0, p1, p2)
#define MCR_REP_36(macro, p0, p1, p2) MCR_REP_35(macro, p0, p1, p2) macro(36, p0, p1, p2)
#define MCR_REP_37(macro, p0, p1, p2) MCR_REP_36(macro, p0, p1, p2) macro(37, p0, p1, p2)
#define MCR_REP_38(macro, p0, p1, p2) MCR_REP_37(macro, p0, p1, p2) macro(38, p0, p1, p2)
#define MCR_REP_39(macro, p0, p1, p2) MCR_REP_38(macro, p0, p1, p2) macro(39, p0, p1, p2)
#define MCR_REP_40(macro, p0, p1, p2) MCR_REP_39(macro, p0, p1, p2) macro(40, p0, p1, p2)
#define MCR_REP_41(macro, p0, p1, p2) MCR_REP_40(macro, p0, p1, p2) macro(41, p0, p1, p2)
#define MCR_REP_42(macro, p0, p1, p2) MCR_REP_41(macro, p0, p1, p2) macro(42, p0, p1, p2)
#define MCR_REP_43(macro, p0, p1, p2) MCR_REP_42(macro, p0, p1, p2) macro(43, p0, p1, p2)
#define MCR_REP_44(macro, p0, p1, p2) MCR_REP_43(macro, p0, p1, p2) macro(44, p0, p1, p2)
#define MCR_REP_45(macro, p0, p1, p2) MCR_REP_44(macro, p0, p1, p2) macro(45, p0, p1, p2)
#define MCR_REP_46(macro, p0, p1, p2) MCR_REP_45(macro, p0, p1, p2) macro(46, p0, p1, p2)
#define MCR_REP_47(macro, p0, p1, p2) MCR_REP_46(macro, p0, p1, p2) macro(47, p0, p1, p2)
#define MCR_REP_48(macro, p0, p1, p2) MCR_REP_47(macro, p0, p1, p2) macro(48, p0, p1, p2)
#define MCR_REP_49(macro, p0, p1, p2) MCR_REP_48(macro, p0, p1, p2) macro(49, p0, p1, p2)
#define MCR_REP_50(macro, p0, p1, p2) MCR_REP_49(macro, p0, p1, p2) macro(50, p0, p1, p2)
#define MCR_REP_51(macro, p0, p1, p2) MCR_REP_50(macro, p0, p1, p2) macro(51, p0, p1, p2)
#define MCR_REP_52(macro, p0, p1, p2) MCR_REP_51(macro, p0, p1, p2) macro(52, p0, p1, p2)
#define MCR_REP_53(macro, p0, p1, p2) MCR_REP_52(macro, p0, p1, p2) macro(53, p0, p1, p2)
#define MCR_REP_54(macro, p0, p1, p2) MCR_REP_53(macro, p0, p1, p2) macro(54, p0, p1, p2)
#define MCR_REP_55(macro, p0, p1, p2) MCR_REP_54(macro, p0, p1, p2) macro(55, p0, p1, p2)
#define MCR_REP_56(macro, p0, p1, p2) MCR_REP_55(macro, p0, p1, p2) macro(56, p0, p1, p2)
#define MCR_REP_57(macro, p0, p1, p2) MCR_REP_56(macro, p0, p1, p2) macro(57, p0, p1, p2)
#define MCR_REP_58(macro, p0, p1, p2) MCR_REP_57(macro, p0, p1, p2) macro(58, p0, p1, p2)
#define MCR_REP_59(macro, p0, p1, p2) MCR_REP_58(macro, p0, p1, p2) macro(59, p0, p1, p2)
#define MCR_REP_60(macro, p0, p1, p2) MCR_REP_59(macro, p0, p1, p2) macro(60, p0, p1, p2)
#define MCR_REP_61(macro, p0, p1, p2) MCR_REP_60(macro, p0, p1, p2) macro(61, p0, p1, p2)
#define MCR_REP_62(macro, p0, p1, p2) MCR_REP_61(macro, p0, p1, p2) macro(62, p0, p1, p2)
#define MCR_REP_63(macro, p0, p1, p2) MCR_REP_62(macro, p0, p1, p2) macro(63, p0, p1, p2)
#define MCR_REP_64(macro, p0, p1, p2) MCR_REP_63(macro, p0, p1, p2) macro(64, p0, p1, p2)
#define MCR_REP_65(macro, p0, p1, p2) MCR_REP_64(macro, p0, p1, p2) macro(65, p0, p1, p2)
#define MCR_REP_66(macro, p0, p1, p2) MCR_REP_65(macro, p0, p1, p2) macro(66, p0, p1, p2)
#define MCR_REP_67(macro, p0, p1, p2) MCR_REP_66(macro, p0, p1, p2) macro(67, p0, p1, p2)
#define MCR_REP_68(macro, p0, p1, p2) MCR_REP_67(macro, p0, p1, p2) macro(68, p0, p1, p2)
#define MCR_REP_69(macro, p0, p1, p2) MCR_REP_68(macro, p0, p1, p2) macro(69, p0, p1, p2)
#define MCR_REP_70(macro, p0, p1, p2) MCR_REP_69(macro, p0, p1, p2) macro(70, p0, p1, p2)
#define MCR_REP_71(macro, p0, p1, p2) MCR_REP_70(macro, p0, p1, p2) macro(71, p0, p1, p2)
#define MCR_REP_72(macro, p0, p1, p2) MCR_REP_71(macro, p0, p1, p2) macro(72, p0, p1, p2)
#define MCR_REP_73(macro, p0, p1, p2) MCR_REP_72(macro, p0, p1, p2) macro(73, p0, p1, p2)
#define MCR_REP_74(macro, p0, p1, p2) MCR_REP_73(macro, p0, p1, p2) macro(74, p0, p1, p2)
#define MCR_REP_75(macro, p0, p1, p2) MCR_REP_74(macro, p0, p1, p2) macro(75, p0, p1, p2)
#define MCR_REP_76(macro, p0, p1, p2) MCR_REP_75(macro, p0, p1, p2) macro(76, p0, p1, p2)
#define MCR_REP_77(macro, p0, p1, p2) MCR_REP_76(macro, p0, p1, p2) macro(77, p0, p1, p2)
#define MCR_REP_78(macro, p0, p1, p2) MCR_REP_77(macro, p0, p1, p2) macro(78, p0, p1, p2)
#define MCR_REP_79(macro, p0, p1, p2) MCR_REP_78(macro, p0, p1, p2) macro(79, p0, p1, p2)
#define MCR_REP_80(macro, p0, p1, p2) MCR_REP_79(macro, p0, p1, p2) macro(80, p0, p1, p2)
#define MCR_REP_81(macro, p0, p1, p2) MCR_REP_80(macro, p0, p1, p2) macro(81, p0, p1, p2)
#define MCR_REP_82(macro, p0, p1, p2) MCR_REP_81(macro, p0, p1, p2) macro(82, p0, p1, p2)
#define MCR_REP_83(macro, p0, p1, p2) MCR_REP_82(macro, p0, p1, p2) macro(83, p0, p1, p2)
#define MCR_REP_84(macro, p0, p1, p2) MCR_REP_83(macro, p0, p1, p2) macro(84, p0, p1, p2)
#define MCR_REP_85(macro, p0, p1, p2) MCR_REP_84(macro, p0, p1, p2) macro(85, p0, p1, p2)
#define MCR_REP_86(macro, p0, p1, p2) MCR_REP_85(macro, p0, p1, p2) macro(86, p0, p1, p2)
#define MCR_REP_87(macro, p0, p1, p2) MCR_REP_86(macro, p0, p1, p2) macro(87, p0, p1, p2)
#define MCR_REP_88(macro, p0, p1, p2) MCR_REP_87(macro, p0, p1, p2) macro(88, p0, p1, p2)
#define MCR_REP_89(macro, p0, p1, p2) MCR_REP_88(macro, p0, p1, p2) macro(89, p0, p1, p2)
#define MCR_REP_90(macro, p0, p1, p2) MCR_REP_89(macro, p0, p1, p2) macro(90, p0, p1, p2)
#define MCR_REP_91(macro, p0, p1, p2) MCR_REP_90(macro, p0, p1, p2) macro(91, p0, p1, p2)
#define MCR_REP_92(macro, p0, p1, p2) MCR_REP_91(macro, p0, p1, p2) macro(92, p0, p1, p2)
#define MCR_REP_93(macro, p0, p1, p2) MCR_REP_92(macro, p0, p1, p2) macro(93, p0, p1, p2)
#define MCR_REP_94(macro, p0, p1, p2) MCR_REP_93(macro, p0, p1, p2) macro(94, p0, p1, p2)
#define MCR_REP_95(macro, p0, p1, p2) MCR_REP_94(macro, p0, p1, p2) macro(95, p0, p1, p2)
#define MCR_REP_96(macro, p0, p1, p2) MCR_REP_95(macro, p0, p1, p2) macro(96, p0, p1, p2)
#define MCR_REP_97(macro, p0, p1, p2) MCR_REP_96(macro, p0, p1, p2) macro(97, p0, p1, p2)
#define MCR_REP_98(macro, p0, p1, p2) MCR_REP_97(macro, p0, p1, p2) macro(98, p0, p1, p2)
#define MCR_REP_99(macro, p0, p1, p2) MCR_REP_98(macro, p0, p1, p2) macro(99, p0, p1, p2)
#define MCR_REP_100(macro, p0, p1, p2) MCR_REP_99(macro, p0, p1, p2) macro(100, p0, p1, p2)
#define MCR_REP_101(macro, p0, p1, p2) MCR_REP_100(macro, p0, p1, p2) macro(101, p0, p1, p2)
#define MCR_REP_102(macro, p0, p1, p2) MCR_REP_101(macro, p0, p1, p2) macro(102, p0, p1, p2)
#define MCR_REP_103(macro, p0, p1, p2) MCR_REP_102(macro, p0, p1, p2) macro(103, p0, p1, p2)
#define MCR_REP_104(macro, p0, p1, p2) MCR_REP_103(macro, p0, p1, p2) macro(104, p0, p1, p2)
#define MCR_REP_105(macro, p0, p1, p2) MCR_REP_104(macro, p0, p1, p2) macro(105, p0, p1, p2)
#define MCR_REP_106(macro, p0, p1, p2) MCR_REP_105(macro, p0, p1, p2) macro(106, p0, p1, p2)
#define MCR_REP_107(macro, p0, p1, p2) MCR_REP_106(macro, p0, p1, p2) macro(107, p0, p1, p2)
#define MCR_REP_108(macro, p0, p1, p2) MCR_REP_107(macro, p0, p1, p2) macro(108, p0, p1, p2)
#define MCR_REP_109(macro, p0, p1, p2) MCR_REP_108(macro, p0, p1, p2) macro(109, p0, p1, p2)
#define MCR_REP_110(macro, p0, p1, p2) MCR_REP_109(macro, p0, p1, p2) macro(110, p0, p1, p2)
#define MCR_REP_111(macro, p0, p1, p2) MCR_REP_110(macro, p0, p1, p2) macro(111, p0, p1, p2)
#define MCR_REP_112(macro, p0, p1, p2) MCR_REP_111(macro, p0, p1, p2) macro(112, p0, p1, p2)
#define MCR_REP_113(macro, p0, p1, p2) MCR_REP_112(macro, p0, p1, p2) macro(113, p0, p1, p2)
#define MCR_REP_114(macro, p0, p1, p2) MCR_REP_113(macro, p0, p1, p2) macro(114, p0, p1, p2)
#define MCR_REP_115(macro, p0, p1, p2) MCR_REP_114(macro, p0, p1, p2) macro(115, p0, p1, p2)
#define MCR_REP_116(macro, p0, p1, p2) MCR_REP_115(macro, p0, p1, p2) macro(116, p0, p1, p2)
#define MCR_REP_117(macro, p0, p1, p2) MCR_REP_116(macro, p0, p1, p2) macro(117, p0, p1, p2)
#define MCR_REP_118(macro, p0, p1, p2) MCR_REP_117(macro, p0, p1, p2) macro(118, p0, p1, p2)
#define MCR_REP_119(macro, p0, p1, p2) MCR_REP_118(macro, p0, p1, p2) macro(119, p0, p1, p2)
#define MCR_REP_120(macro, p0, p1, p2) MCR_REP_119(macro, p0, p1, p2) macro(120, p0, p1, p2)
#define MCR_REP_121(macro, p0, p1, p2) MCR_REP_120(macro, p0, p1, p2) macro(121, p0, p1, p2)
#define MCR_REP_122(macro, p0, p1, p2) MCR_REP_121(macro, p0, p1, p2) macro(122, p0, p1, p2)
#define MCR_REP_123(macro, p0, p1, p2) MCR_REP_122(macro, p0, p1, p2) macro(123, p0, p1, p2)
#define MCR_REP_124(macro, p0, p1, p2) MCR_REP_123(macro, p0, p1, p2) macro(124, p0, p1, p2)
#define MCR_REP_125(macro, p0, p1, p2) MCR_REP_124(macro, p0, p1, p2) macro(125, p0, p1, p2)
#define MCR_REP_126(macro, p0, p1, p2) MCR_REP_125(macro, p0, p1, p2) macro(126, p0, p1, p2)
#define MCR_REP_127(macro, p0, p1, p2) MCR_REP_126(macro, p0, p1, p2) macro(127, p0, p1, p2)
#define MCR_REP_128(macro, p0, p1, p2) MCR_REP_127(macro, p0, p1, p2) macro(128, p0, p1, p2)
#define MCR_REP_129(macro, p0, p1, p2) MCR_REP_128(macro, p0, p1, p2) macro(129, p0, p1, p2)
#define MCR_REP_130(macro, p0, p1, p2) MCR_REP_129(macro, p0, p1, p2) macro(130, p0, p1, p2)
#define MCR_REP_131(macro, p0, p1, p2) MCR_REP_130(macro, p0, p1, p2) macro(131, p0, p1, p2)
#define MCR_REP_132(macro, p0, p1, p2) MCR_REP_131(macro, p0, p1, p2) macro(132, p0, p1, p2)
#define MCR_REP_133(macro, p0, p1, p2) MCR_REP_132(macro, p0, p1, p2) macro(133, p0, p1, p2)
#define MCR_REP_134(macro, p0, p1, p2) MCR_REP_133(macro, p0, p1, p2) macro(134, p0, p1, p2)
#define MCR_REP_135(macro, p0, p1, p2) MCR_REP_134(macro, p0, p1, p2) macro(135, p0, p1, p2)
#define MCR_REP_136(macro, p0, p1, p2) MCR_REP_135(macro, p0, p1, p2) macro(136, p0, p1, p2)
#define MCR_REP_137(macro, p0, p1, p2) MCR_REP_136(macro, p0, p1, p2) macro(137, p0, p1, p2)
#define MCR_REP_138(macro, p0, p1, p2) MCR_REP_137(macro, p0, p1, p2) macro(138, p0, p1, p2)
#define MCR_REP_139(macro, p0, p1, p2) MCR_REP_138(macro, p0, p1, p2) macro(139, p0, p1, p2)
#define MCR_REP_140(macro, p0, p1, p2) MCR_REP_139(macro, p0, p1, p2) macro(140, p0, p1, p2)
#define MCR_REP_141(macro, p0, p1, p2) MCR_REP_140(macro, p0, p1, p2) macro(141, p0, p1, p2)
#define MCR_REP_142(macro, p0, p1, p2) MCR_REP_141(macro, p0, p1, p2) macro(142, p0, p1, p2)
#define MCR_REP_143(macro, p0, p1, p2) MCR_REP_142(macro, p0, p1, p2) macro(143, p0, p1, p2)
#define MCR_REP_144(macro, p0, p1, p2) MCR_REP_143(macro, p0, p1, p2) macro(144, p0, p1, p2)
#define MCR_REP_145(macro, p0, p1, p2) MCR_REP_144(macro, p0, p1, p2) macro(145, p0, p1, p2)
#define MCR_REP_146(macro, p0, p1, p2) MCR_REP_145(macro, p0, p1, p2) macro(146, p0, p1, p2)
#define MCR_REP_147(macro, p0, p1, p2) MCR_REP_146(macro, p0, p1, p2) macro(147, p0, p1, p2)
#define MCR_REP_148(macro, p0, p1, p2) MCR_REP_147(macro, p0, p1, p2) macro(148, p0, p1, p2)
#define MCR_REP_149(macro, p0, p1, p2) MCR_REP_148(macro, p0, p1, p2) macro(149, p0, p1, p2)
#define MCR_REP_150(macro, p0, p1, p2) MCR_REP_149(macro, p0, p1, p2) macro(150, p0, p1, p2)
#define MCR_REP_151(macro, p0, p1, p2) MCR_REP_150(macro, p0, p1, p2) macro(151, p0, p1, p2)
#define MCR_REP_152(macro, p0, p1, p2) MCR_REP_151(macro, p0, p1, p2) macro(152, p0, p1, p2)
#define MCR_REP_153(macro, p0, p1, p2) MCR_REP_152(macro, p0, p1, p2) macro(153, p0, p1, p2)
#define MCR_REP_154(macro, p0, p1, p2) MCR_REP_153(macro, p0, p1, p2) macro(154, p0, p1, p2)
#define MCR_REP_155(macro, p0, p1, p2) MCR_REP_154(macro, p0, p1, p2) macro(155, p0, p1, p2)
#define MCR_REP_156(macro, p0, p1, p2) MCR_REP_155(macro, p0, p1, p2) macro(156, p0, p1, p2)
#define MCR_REP_157(macro, p0, p1, p2) MCR_REP_156(macro, p0, p1, p2) macro(157, p0, p1, p2)
#define MCR_REP_158(macro, p0, p1, p2) MCR_REP_157(macro, p0, p1, p2) macro(158, p0, p1, p2)
#define MCR_REP_159(macro, p0, p1, p2) MCR_REP_158(macro, p0, p1, p2) macro(159, p0, p1, p2)
#define MCR_REP_160(macro, p0, p1, p2) MCR_REP_159(macro, p0, p1, p2) macro(160, p0, p1, p2)
#define MCR_REP_161(macro, p0, p1, p2) MCR_REP_160(macro, p0, p1, p2) macro(161, p0, p1, p2)
#define MCR_REP_162(macro, p0, p1, p2) MCR_REP_161(macro, p0, p1, p2) macro(162, p0, p1, p2)
#define MCR_REP_163(macro, p0, p1, p2) MCR_REP_162(macro, p0, p1, p2) macro(163, p0, p1, p2)
#define MCR_REP_164(macro, p0, p1, p2) MCR_REP_163(macro, p0, p1, p2) macro(164, p0, p1, p2)
#define MCR_REP_165(macro, p0, p1, p2) MCR_REP_164(macro, p0, p1, p2) macro(165, p0, p1, p2)
#define MCR_REP_166(macro, p0, p1, p2) MCR_REP_165(macro, p0, p1, p2) macro(166, p0, p1, p2)
#define MCR_REP_167(macro, p0, p1, p2) MCR_REP_166(macro, p0, p1, p2) macro(167, p0, p1, p2)
#define MCR_REP_168(macro, p0, p1, p2) MCR_REP_167(macro, p0, p1, p2) macro(168, p0, p1, p2)
#define MCR_REP_169(macro, p0, p1, p2) MCR_REP_168(macro, p0, p1, p2) macro(169, p0, p1, p2)
#define MCR_REP_170(macro, p0, p1, p2) MCR_REP_169(macro, p0, p1, p2) macro(170, p0, p1, p2)
#define MCR_REP_171(macro, p0, p1, p2) MCR_REP_170(macro, p0, p1, p2) macro(171, p0, p1, p2)
#define MCR_REP_172(macro, p0, p1, p2) MCR_REP_171(macro, p0, p1, p2) macro(172, p0, p1, p2)
#define MCR_REP_173(macro, p0, p1, p2) MCR_REP_172(macro, p0, p1, p2) macro(173, p0, p1, p2)
#define MCR_REP_174(macro, p0, p1, p2) MCR_REP_173(macro, p0, p1, p2) macro(174, p0, p1, p2)
#define MCR_REP_175(macro, p0, p1, p2) MCR_REP_174(macro, p0, p1, p2) macro(175, p0, p1, p2)
#define MCR_REP_176(macro, p0, p1, p2) MCR_REP_175(macro, p0, p1, p2) macro(176, p0, p1, p2)
#define MCR_REP_177(macro, p0, p1, p2) MCR_REP_176(macro, p0, p1, p2) macro(177, p0, p1, p2)
#define MCR_REP_178(macro, p0, p1, p2) MCR_REP_177(macro, p0, p1, p2) macro(178, p0, p1, p2)
#define MCR_REP_179(macro, p0, p1, p2) MCR_REP_178(macro, p0, p1, p2) macro(179, p0, p1, p2)
#define MCR_REP_180(macro, p0, p1, p2) MCR_REP_179(macro, p0, p1, p2) macro(180, p0, p1, p2)
#define MCR_REP_181(macro, p0, p1, p2) MCR_REP_180(macro, p0, p1, p2) macro(181, p0, p1, p2)
#define MCR_REP_182(macro, p0, p1, p2) MCR_REP_181(macro, p0, p1, p2) macro(182, p0, p1, p2)
#define MCR_REP_183(macro, p0, p1, p2) MCR_REP_182(macro, p0, p1, p2) macro(183, p0, p1, p2)
#define MCR_REP_184(macro, p0, p1, p2) MCR_REP_183(macro, p0, p1, p2) macro(184, p0, p1, p2)
#define MCR_REP_185(macro, p0, p1, p2) MCR_REP_184(macro, p0, p1, p2) macro(185, p0, p1, p2)
#define MCR_REP_186(macro, p0, p1, p2) MCR_REP_185(macro, p0, p1, p2) macro(186, p0, p1, p2)
#define MCR_REP_187(macro, p0, p1, p2) MCR_REP_186(macro, p0, p1, p2) macro(187, p0, p1, p2)
#define MCR_REP_188(macro, p0, p1, p2) MCR_REP_187(macro, p0, p1, p2) macro(188, p0, p1, p2)
#define MCR_REP_189(macro, p0, p1, p2) MCR_REP_188(macro, p0, p1, p2) macro(189, p0, p1, p2)
#define MCR_REP_190(macro, p0, p1, p2) MCR_REP_189(macro, p0, p1, p2) macro(190, p0, p1, p2)
#define MCR_REP_191(macro, p0, p1, p2) MCR_REP_190(macro, p0, p1, p2) macro(191, p0, p1, p2)
#define MCR_REP_192(macro, p0, p1, p2) MCR_REP_191(macro, p0, p1, p2) macro(192, p0, p1, p2)
#define MCR_REP_193(macro, p0, p1, p2) MCR_REP_192(macro, p0, p1, p2) macro(193, p0, p1, p2)
#define MCR_REP_194(macro, p0, p1, p2) MCR_REP_193(macro, p0, p1, p2) macro(194, p0, p1, p2)
#define MCR_REP_195(macro, p0, p1, p2) MCR_REP_194(macro, p0, p1, p2) macro(195, p0, p1, p2)
#define MCR_REP_196(macro, p0, p1, p2) MCR_REP_195(macro, p0, p1, p2) macro(196, p0, p1, p2)
#define MCR_REP_197(macro, p0, p1, p2) MCR_REP_196(macro, p0, p1, p2) macro(197, p0, p1, p2)
#define MCR_REP_198(macro, p0, p1, p2) MCR_REP_197(macro, p0, p1, p2) macro(198, p0, p1, p2)
#define MCR_REP_199(macro, p0, p1, p2) MCR_REP_198(macro, p0, p1, p2) macro(199, p0, p1, p2)
#define MCR_REP_200(macro, p0, p1, p2) MCR_REP_199(macro, p0, p1, p2) macro(200, p0, p1, p2)
#define MCR_REP_201(macro, p0, p1, p2) MCR_REP_200(macro, p0, p1, p2) macro(201, p0, p1, p2)
#define MCR_REP_202(macro, p0, p1, p2) MCR_REP_201(macro, p0, p1, p2) macro(202, p0, p1, p2)
#define MCR_REP_203(macro, p0, p1, p2) MCR_REP_202(macro, p0, p1, p2) macro(203, p0, p1, p2)
#define MCR_REP_204(macro, p0, p1, p2) MCR_REP_203(macro, p0, p1, p2) macro(204, p0, p1, p2)
#define MCR_REP_205(macro, p0, p1, p2) MCR_REP_204(macro, p0, p1, p2) macro(205, p0, p1, p2)
#define MCR_REP_206(macro, p0, p1, p2) MCR_REP_205(macro, p0, p1, p2) macro(206, p0, p1, p2)
#define MCR_REP_207(macro, p0, p1, p2) MCR_REP_206(macro, p0, p1, p2) macro(207, p0, p1, p2)
#define MCR_REP_208(macro, p0, p1, p2) MCR_REP_207(macro, p0, p1, p2) macro(208, p0, p1, p2)
#define MCR_REP_209(macro, p0, p1, p2) MCR_REP_208(macro, p0, p1, p2) macro(209, p0, p1, p2)
#define MCR_REP_210(macro, p0, p1, p2) MCR_REP_209(macro, p0, p1, p2) macro(210, p0, p1, p2)
#define MCR_REP_211(macro, p0, p1, p2) MCR_REP_210(macro, p0, p1, p2) macro(211, p0, p1, p2)
#define MCR_REP_212(macro, p0, p1, p2) MCR_REP_211(macro, p0, p1, p2) macro(212, p0, p1, p2)
#define MCR_REP_213(macro, p0, p1, p2) MCR_REP_212(macro, p0, p1, p2) macro(213, p0, p1, p2)
#define MCR_REP_214(macro, p0, p1, p2) MCR_REP_213(macro, p0, p1, p2) macro(214, p0, p1, p2)
#define MCR_REP_215(macro, p0, p1, p2) MCR_REP_214(macro, p0, p1, p2) macro(215, p0, p1, p2)
#define MCR_REP_216(macro, p0, p1, p2) MCR_REP_215(macro, p0, p1, p2) macro(216, p0, p1, p2)
#define MCR_REP_217(macro, p0, p1, p2) MCR_REP_216(macro, p0, p1, p2) macro(217, p0, p1, p2)
#define MCR_REP_218(macro, p0, p1, p2) MCR_REP_217(macro, p0, p1, p2) macro(218, p0, p1, p2)
#define MCR_REP_219(macro, p0, p1, p2) MCR_REP_218(macro, p0, p1, p2) macro(219, p0, p1, p2)
#define MCR_REP_220(macro, p0, p1, p2) MCR_REP_219(macro, p0, p1, p2) macro(220, p0, p1, p2)
#define MCR_REP_221(macro, p0, p1, p2) MCR_REP_220(macro, p0, p1, p2) macro(221, p0, p1, p2)
#define MCR_REP_222(macro, p0, p1, p2) MCR_REP_221(macro, p0, p1, p2) macro(222, p0, p1, p2)
#define MCR_REP_223(macro, p0, p1, p2) MCR_REP_222(macro, p0, p1, p2) macro(223, p0, p1, p2)
#define MCR_REP_224(macro, p0, p1, p2) MCR_REP_223(macro, p0, p1, p2) macro(224, p0, p1, p2)
#define MCR_REP_225(macro, p0, p1, p2) MCR_REP_224(macro, p0, p1, p2) macro(225, p0, p1, p2)
#define MCR_REP_226(macro, p0, p1, p2) MCR_REP_225(macro, p0, p1, p2) macro(226, p0, p1, p2)
#define MCR_REP_227(macro, p0, p1, p2) MCR_REP_226(macro, p0, p1, p2) macro(227, p0, p1, p2)
#define MCR_REP_228(macro, p0, p1, p2) MCR_REP_227(macro, p0, p1, p2) macro(228, p0, p1, p2)
#define MCR_REP_229(macro, p0, p1, p2) MCR_REP_228(macro, p0, p1, p2) macro(229, p0, p1, p2)
#define MCR_REP_230(macro, p0, p1, p2) MCR_REP_229(macro, p0, p1, p2) macro(230, p0, p1, p2)
#define MCR_REP_231(macro, p0, p1, p2) MCR_REP_230(macro, p0, p1, p2) macro(231, p0, p1, p2)
#define MCR_REP_232(macro, p0, p1, p2) MCR_REP_231(macro, p0, p1, p2) macro(232, p0, p1, p2)
#define MCR_REP_233(macro, p0, p1, p2) MCR_REP_232(macro, p0, p1, p2) macro(233, p0, p1, p2)
#define MCR_REP_234(macro, p0, p1, p2) MCR_REP_233(macro, p0, p1, p2) macro(234, p0, p1, p2)
#define MCR_REP_235(macro, p0, p1, p2) MCR_REP_234(macro, p0, p1, p2) macro(235, p0, p1, p2)
#define MCR_REP_236(macro, p0, p1, p2) MCR_REP_235(macro, p0, p1, p2) macro(236, p0, p1, p2)
#define MCR_REP_237(macro, p0, p1, p2) MCR_REP_236(macro, p0, p1, p2) macro(237, p0, p1, p2)
#define MCR_REP_238(macro, p0, p1, p2) MCR_REP_237(macro, p0, p1, p2) macro(238, p0, p1, p2)
#define MCR_REP_239(macro, p0, p1, p2) MCR_REP_238(macro, p0, p1, p2) macro(239, p0, p1, p2)
#define MCR_REP_240(macro, p0, p1, p2) MCR_REP_239(macro, p0, p1, p2) macro(240, p0, p1, p2)
#define MCR_REP_241(macro, p0, p1, p2) MCR_REP_240(macro, p0, p1, p2) macro(241, p0, p1, p2)
#define MCR_REP_242(macro, p0, p1, p2) MCR_REP_241(macro, p0, p1, p2) macro(242, p0, p1, p2)
#define MCR_REP_243(macro, p0, p1, p2) MCR_REP_242(macro, p0, p1, p2) macro(243, p0, p1, p2)
#define MCR_REP_244(macro, p0, p1, p2) MCR_REP_243(macro, p0, p1, p2) macro(244, p0, p1, p2)
#define MCR_REP_245(macro, p0, p1, p2) MCR_REP_244(macro, p0, p1, p2) macro(245, p0, p1, p2)
#define MCR_REP_246(macro, p0, p1, p2) MCR_REP_245(macro, p0, p1, p2) macro(246, p0, p1, p2)
#define MCR_REP_247(macro, p0, p1, p2) MCR_REP_246(macro, p0, p1, p2) macro(247, p0, p1, p2)
#define MCR_REP_248(macro, p0, p1, p2) MCR_REP_247(macro, p0, p1, p2) macro(248, p0, p1, p2)
#define MCR_REP_249(macro, p0, p1, p2) MCR_REP_248(macro, p0, p1, p2) macro(249, p0, p1, p2)
#define MCR_REP_250(macro, p0, p1, p2) MCR_REP_249(macro, p0, p1, p2) macro(250, p0, p1, p2)
#define MCR_REP_251(macro, p0, p1, p2) MCR_REP_250(macro, p0, p1, p2) macro(251, p0, p1, p2)
#define MCR_REP_252(macro, p0, p1, p2) MCR_REP_251(macro, p0, p1, p2) macro(252, p0, p1, p2)
#define MCR_REP_253(macro, p0, p1, p2) MCR_REP_252(macro, p0, p1, p2) macro(253, p0, p1, p2)
#define MCR_REP_254(macro, p0, p1, p2) MCR_REP_253(macro, p0, p1, p2) macro(254, p0, p1, p2)
#define MCR_REP_255(macro, p0, p1, p2) MCR_REP_254(macro, p0, p1, p2) macro(255, p0, p1, p2)
#define MCR_REP_256(macro, p0, p1, p2) MCR_REP_255(macro, p0, p1, p2) macro(256, p0, p1, p2)
#define MCR_REP_257(macro, p0, p1, p2) MCR_REP_256(macro, p0, p1, p2) macro(257, p0, p1, p2)
#define MCR_REP_258(macro, p0, p1, p2) MCR_REP_257(macro, p0, p1, p2) macro(258, p0, p1, p2)
#define MCR_REP_259(macro, p0, p1, p2) MCR_REP_258(macro, p0, p1, p2) macro(259, p0, p1, p2)
#define MCR_REP_260(macro, p0, p1, p2) MCR_REP_259(macro, p0, p1, p2) macro(260, p0, p1, p2)
#define MCR_REP_261(macro, p0, p1, p2) MCR_REP_260(macro, p0, p1, p2) macro(261, p0, p1, p2)
#define MCR_REP_262(macro, p0, p1, p2) MCR_REP_261(macro, p0, p1, p2) macro(262, p0, p1, p2)
#define MCR_REP_263(macro, p0, p1, p2) MCR_REP_262(macro, p0, p1, p2) macro(263, p0, p1, p2)
#define MCR_REP_264(macro, p0, p1, p2) MCR_REP_263(macro, p0, p1, p2) macro(264, p0, p1, p2)
#define MCR_REP_265(macro, p0, p1, p2) MCR_REP_264(macro, p0, p1, p2) macro(265, p0, p1, p2)
#define MCR_REP_266(macro, p0, p1, p2) MCR_REP_265(macro, p0, p1, p2) macro(266, p0, p1, p2)
#define MCR_REP_267(macro, p0, p1, p2) MCR_REP_266(macro, p0, p1, p2) macro(267, p0, p1, p2)
#define MCR_REP_268(macro, p0, p1, p2) MCR_REP_267(macro, p0, p1, p2) macro(268, p0, p1, p2)
#define MCR_REP_269(macro, p0, p1, p2) MCR_REP_268(macro, p0, p1, p2) macro(269, p0, p1, p2)
#define MCR_REP_270(macro, p0, p1, p2) MCR_REP_269(macro, p0, p1, p2) macro(270, p0, p1, p2)
#define MCR_REP_271(macro, p0, p1, p2) MCR_REP_270(macro, p0, p1, p2) macro(271, p0, p1, p2)
#define MCR_REP_272(macro, p0, p1, p2) MCR_REP_271(macro, p0, p1, p2) macro(272, p0, p1, p2)
#define MCR_REP_273(macro, p0, p1, p2) MCR_REP_272(macro, p0, p1, p2) macro(273, p0, p1, p2)
#define MCR_REP_274(macro, p0, p1, p2) MCR_REP_273(macro, p0, p1, p2) macro(274, p0, p1, p2)
#define MCR_REP_275(macro, p0, p1, p2) MCR_REP_274(macro, p0, p1, p2) macro(275, p0, p1, p2)
#define MCR_REP_276(macro, p0, p1, p2) MCR_REP_275(macro, p0, p1, p2) macro(276, p0, p1, p2)
#define MCR_REP_277(macro, p0, p1, p2) MCR_REP_276(macro, p0, p1, p2) macro(277, p0, p1, p2)
#define MCR_REP_278(macro, p0, p1, p2) MCR_REP_277(macro, p0, p1, p2) macro(278, p0, p1, p2)
#define MCR_REP_279(macro, p0, p1, p2) MCR_REP_278(macro, p0, p1, p2) macro(279, p0, p1, p2)
#define MCR_REP_280(macro, p0, p1, p2) MCR_REP_279(macro, p0, p1, p2) macro(280, p0, p1, p2)
#define MCR_REP_281(macro, p0, p1, p2) MCR_REP_280(macro, p0, p1, p2) macro(281, p0, p1, p2)
#define MCR_REP_282(macro, p0, p1, p2) MCR_REP_281(macro, p0, p1, p2) macro(282, p0, p1, p2)
#define MCR_REP_283(macro, p0, p1, p2) MCR_REP_282(macro, p0, p1, p2) macro(283, p0, p1, p2)
#define MCR_REP_284(macro, p0, p1, p2) MCR_REP_283(macro, p0, p1, p2) macro(284, p0, p1, p2)
#define MCR_REP_285(macro, p0, p1, p2) MCR_REP_284(macro, p0, p1, p2) macro(285, p0, p1, p2)
#define MCR_REP_286(macro, p0, p1, p2) MCR_REP_285(macro, p0, p1, p2) macro(286, p0, p1, p2)
#define MCR_REP_287(macro, p0, p1, p2) MCR_REP_286(macro, p0, p1, p2) macro(287, p0, p1, p2)
#define MCR_REP_288(macro, p0, p1, p2) MCR_REP_287(macro, p0, p1, p2) macro(288, p0, p1, p2)
#define MCR_REP_289(macro, p0, p1, p2) MCR_REP_288(macro, p0, p1, p2) macro(289, p0, p1, p2)
#define MCR_REP_290(macro, p0, p1, p2) MCR_REP_289(macro, p0, p1, p2) macro(290, p0, p1, p2)
#define MCR_REP_291(macro, p0, p1, p2) MCR_REP_290(macro, p0, p1, p2) macro(291, p0, p1, p2)
#define MCR_REP_292(macro, p0, p1, p2) MCR_REP_291(macro, p0, p1, p2) macro(292, p0, p1, p2)
#define MCR_REP_293(macro, p0, p1, p2) MCR_REP_292(macro, p0, p1, p2) macro(293, p0, p1, p2)
#define MCR_REP_294(macro, p0, p1, p2) MCR_REP_293(macro, p0, p1, p2) macro(294, p0, p1, p2)
#define MCR_REP_295(macro, p0, p1, p2) MCR_REP_294(macro, p0, p1, p2) macro(295, p0, p1, p2)
#define MCR_REP_296(macro, p0, p1, p2) MCR_REP_295(macro, p0, p1, p2) macro(296, p0, p1, p2)
#define MCR_REP_297(macro, p0, p1, p2) MCR_REP_296(macro, p0, p1, p2) macro(297, p0, p1, p2)
#define MCR_REP_298(macro, p0, p1, p2) MCR_REP_297(macro, p0, p1, p2) macro(298, p0, p1, p2)
#define MCR_REP_299(macro, p0, p1, p2) MCR_REP_298(macro, p0, p1, p2) macro(299, p0, p1, p2)
#define MCR_REP_300(macro, p0, p1, p2) MCR_REP_299(macro, p0, p1, p2) macro(300, p0, p1, p2)
#define MCR_REP_301(macro, p0, p1, p2) MCR_REP_300(macro, p0, p1, p2) macro(301, p0, p1, p2)
#define MCR_REP_302(macro, p0, p1, p2) MCR_REP_301(macro, p0, p1, p2) macro(302, p0, p1, p2)
#define MCR_REP_303(macro, p0, p1, p2) MCR_REP_302(macro, p0, p1, p2) macro(303, p0, p1, p2)
#define MCR_REP_304(macro, p0, p1, p2) MCR_REP_303(macro, p0, p1, p2) macro(304, p0, p1, p2)
#define MCR_REP_305(macro, p0, p1, p2) MCR_REP_304(macro, p0, p1, p2) macro(305, p0, p1, p2)
#define MCR_REP_306(macro, p0, p1, p2) MCR_REP_305(macro, p0, p1, p2) macro(306, p0, p1, p2)
#define MCR_REP_307(macro, p0, p1, p2) MCR_REP_306(macro, p0, p1, p2) macro(307, p0, p1, p2)
#define MCR_REP_308(macro, p0, p1, p2) MCR_REP_307(macro, p0, p1, p2) macro(308, p0, p1, p2)
#define MCR_REP_309(macro, p0, p1, p2) MCR_REP_308(macro, p0, p1, p2) macro(309, p0, p1, p2)
#define MCR_REP_310(macro, p0, p1, p2) MCR_REP_309(macro, p0, p1, p2) macro(310, p0, p1, p2)
#define MCR_REP_311(macro, p0, p1, p2) MCR_REP_310(macro, p0, p1, p2) macro(311, p0, p1, p2)
#define MCR_REP_312(macro, p0, p1, p2) MCR_REP_311(macro, p0, p1, p2) macro(312, p0, p1, p2)
#define MCR_REP_313(macro, p0, p1, p2) MCR_REP_312(macro, p0, p1, p2) macro(313, p0, p1, p2)
#define MCR_REP_314(macro, p0, p1, p2) MCR_REP_313(macro, p0, p1, p2) macro(314, p0, p1, p2)
#define MCR_REP_315(macro, p0, p1, p2) MCR_REP_314(macro, p0, p1, p2) macro(315, p0, p1, p2)
#define MCR_REP_316(macro, p0, p1, p2) MCR_REP_315(macro, p0, p1, p2) macro(316, p0, p1, p2)
#define MCR_REP_317(macro, p0, p1, p2) MCR_REP_316(macro, p0, p1, p2) macro(317, p0, p1, p2)
#define MCR_REP_318(macro, p0, p1, p2) MCR_REP_317(macro, p0, p1, p2) macro(318, p0, p1, p2)
#define MCR_REP_319(macro, p0, p1, p2) MCR_REP_318(macro, p0, p1, p2) macro(319, p0, p1, p2)
#define MCR_REP_320(macro, p0, p1, p2) MCR_REP_319(macro, p0, p1, p2) macro(320, p0, p1, p2)
#define MCR_REP_321(macro, p0, p1, p2) MCR_REP_320(macro, p0, p1, p2) macro(321, p0, p1, p2)
#define MCR_REP_322(macro, p0, p1, p2) MCR_REP_321(macro, p0, p1, p2) macro(322, p0, p1, p2)
#define MCR_REP_323(macro, p0, p1, p2) MCR_REP_322(macro, p0, p1, p2) macro(323, p0, p1, p2)
#define MCR_REP_324(macro, p0, p1, p2) MCR_REP_323(macro, p0, p1, p2) macro(324, p0, p1, p2)
#define MCR_REP_325(macro, p0, p1, p2) MCR_REP_324(macro, p0, p1, p2) macro(325, p0, p1, p2)
#define MCR_REP_326(macro, p0, p1, p2) MCR_REP_325(macro, p0, p1, p2) macro(326, p0, p1, p2)
#define MCR_REP_327(macro, p0, p1, p2) MCR_REP_326(macro, p0, p1, p2) macro(327, p0, p1, p2)
#define MCR_REP_328(macro, p0, p1, p2) MCR_REP_327(macro, p0, p1, p2) macro(328, p0, p1, p2)
#define MCR_REP_329(macro, p0, p1, p2) MCR_REP_328(macro, p0, p1, p2) macro(329, p0, p1, p2)
#define MCR_REP_330(macro, p0, p1, p2) MCR_REP_329(macro, p0, p1, p2) macro(330, p0, p1, p2)
#define MCR_REP_331(macro, p0, p1, p2) MCR_REP_330(macro, p0, p1, p2) macro(331, p0, p1, p2)
#define MCR_REP_332(macro, p0, p1, p2) MCR_REP_331(macro, p0, p1, p2) macro(332, p0, p1, p2)
#define MCR_REP_333(macro, p0, p1, p2) MCR_REP_332(macro, p0, p1, p2) macro(333, p0, p1, p2)
#define MCR_REP_334(macro, p0, p1, p2) MCR_REP_333(macro, p0, p1, p2) macro(334, p0, p1, p2)
#define MCR_REP_335(macro, p0, p1, p2) MCR_REP_334(macro, p0, p1, p2) macro(335, p0, p1, p2)
#define MCR_REP_336(macro, p0, p1, p2) MCR_REP_335(macro, p0, p1, p2) macro(336, p0, p1, p2)
#define MCR_REP_337(macro, p0, p1, p2) MCR_REP_336(macro, p0, p1, p2) macro(337, p0, p1, p2)
#define MCR_REP_338(macro, p0, p1, p2) MCR_REP_337(macro, p0, p1, p2) macro(338, p0, p1, p2)
#define MCR_REP_339(macro, p0, p1, p2) MCR_REP_338(macro, p0, p1, p2) macro(339, p0, p1, p2)
#define MCR_REP_340(macro, p0, p1, p2) MCR_REP_339(macro, p0, p1, p2) macro(340, p0, p1, p2)
#define MCR_REP_341(macro, p0, p1, p2) MCR_REP_340(macro, p0, p1, p2) macro(341, p0, p1, p2)
#define MCR_REP_342(macro, p0, p1, p2) MCR_REP_341(macro, p0, p1, p2) macro(342, p0, p1, p2)
#define MCR_REP_343(macro, p0, p1, p2) MCR_REP_342(macro, p0, p1, p2) macro(343, p0, p1, p2)
#define MCR_REP_344(macro, p0, p1, p2) MCR_REP_343(macro, p0, p1, p2) macro(344, p0, p1, p2)
#define MCR_REP_345(macro, p0, p1, p2) MCR_REP_344(macro, p0, p1, p2) macro(345, p0, p1, p2)
#define MCR_REP_346(macro, p0, p1, p2) MCR_REP_345(macro, p0, p1, p2) macro(346, p0, p1, p2)
#define MCR_REP_347(macro, p0, p1, p2) MCR_REP_346(macro, p0, p1, p2) macro(347, p0, p1, p2)
#define MCR_REP_348(macro, p0, p1, p2) MCR_REP_347(macro, p0, p1, p2) macro(348, p0, p1, p2)
#define MCR_REP_349(macro, p0, p1, p2) MCR_REP_348(macro, p0, p1, p2) macro(349, p0, p1, p2)
#define MCR_REP_350(macro, p0, p1, p2) MCR_REP_349(macro, p0, p1, p2) macro(350, p0, p1, p2)
#define MCR_REP_351(macro, p0, p1, p2) MCR_REP_350(macro, p0, p1, p2) macro(351, p0, p1, p2)
#define MCR_REP_352(macro, p0, p1, p2) MCR_REP_351(macro, p0, p1, p2) macro(352, p0, p1, p2)
#define MCR_REP_353(macro, p0, p1, p2) MCR_REP_352(macro, p0, p1, p2) macro(353, p0, p1, p2)
#define MCR_REP_354(macro, p0, p1, p2) MCR_REP_353(macro, p0, p1, p2) macro(354, p0, p1, p2)
#define MCR_REP_355(macro, p0, p1, p2) MCR_REP_354(macro, p0, p1, p2) macro(355, p0, p1, p2)
#define MCR_REP_356(macro, p0, p1, p2) MCR_REP_355(macro, p0, p1, p2) macro(356, p0, p1, p2)
#define MCR_REP_357(macro, p0, p1, p2) MCR_REP_356(macro, p0, p1, p2) macro(357, p0, p1, p2)
#define MCR_REP_358(macro, p0, p1, p2) MCR_REP_357(macro, p0, p1, p2) macro(358, p0, p1, p2)
#define MCR_REP_359(macro, p0, p1, p2) MCR_REP_358(macro, p0, p1, p2) macro(359, p0, p1, p2)
#define MCR_REP_360(macro, p0, p1, p2) MCR_REP_359(macro, p0, p1, p2) macro(360, p0, p1, p2)
#define MCR_REP_361(macro, p0, p1, p2) MCR_REP_360(macro, p0, p1, p2) macro(361, p0, p1, p2)
#define MCR_REP_362(macro, p0, p1, p2) MCR_REP_361(macro, p0, p1, p2) macro(362, p0, p1, p2)
#define MCR_REP_363(macro, p0, p1, p2) MCR_REP_362(macro, p0, p1, p2) macro(363, p0, p1, p2)
#define MCR_REP_364(macro, p0, p1, p2) MCR_REP_363(macro, p0, p1, p2) macro(364, p0, p1, p2)
#define MCR_REP_365(macro, p0, p1, p2) MCR_REP_364(macro, p0, p1, p2) macro(365, p0, p1, p2)
#define MCR_REP_366(macro, p0, p1, p2) MCR_REP_365(macro, p0, p1, p2) macro(366, p0, p1, p2)
#define MCR_REP_367(macro, p0, p1, p2) MCR_REP_366(macro, p0, p1, p2) macro(367, p0, p1, p2)
#define MCR_REP_368(macro, p0, p1, p2) MCR_REP_367(macro, p0, p1, p2) macro(368, p0, p1, p2)
#define MCR_REP_369(macro, p0, p1, p2) MCR_REP_368(macro, p0, p1, p2) macro(369, p0, p1, p2)
#define MCR_REP_370(macro, p0, p1, p2) MCR_REP_369(macro, p0, p1, p2) macro(370, p0, p1, p2)
#define MCR_REP_371(macro, p0, p1, p2) MCR_REP_370(macro, p0, p1, p2) macro(371, p0, p1, p2)
#define MCR_REP_372(macro, p0, p1, p2) MCR_REP_371(macro, p0, p1, p2) macro(372, p0, p1, p2)
#define MCR_REP_373(macro, p0, p1, p2) MCR_REP_372(macro, p0, p1, p2) macro(373, p0, p1, p2)
#define MCR_REP_374(macro, p0, p1, p2) MCR_REP_373(macro, p0, p1, p2) macro(374, p0, p1, p2)
#define MCR_REP_375(macro, p0, p1, p2) MCR_REP_374(macro, p0, p1, p2) macro(375, p0, p1, p2)
#define MCR_REP_376(macro, p0, p1, p2) MCR_REP_375(macro, p0, p1, p2) macro(376, p0, p1, p2)
#define MCR_REP_377(macro, p0, p1, p2) MCR_REP_376(macro, p0, p1, p2) macro(377, p0, p1, p2)
#define MCR_REP_378(macro, p0, p1, p2) MCR_REP_377(macro, p0, p1, p2) macro(378, p0, p1, p2)
#define MCR_REP_379(macro, p0, p1, p2) MCR_REP_378(macro, p0, p1, p2) macro(379, p0, p1, p2)
#define MCR_REP_380(macro, p0, p1, p2) MCR_REP_379(macro, p0, p1, p2) macro(380, p0, p1, p2)
#define MCR_REP_381(macro, p0, p1, p2) MCR_REP_380(macro, p0, p1, p2) macro(381, p0, p1, p2)
#define MCR_REP_382(macro, p0, p1, p2) MCR_REP_381(macro, p0, p1, p2) macro(382, p0, p1, p2)
#define MCR_REP_383(macro, p0, p1, p2) MCR_REP_382(macro, p0, p1, p2) macro(383, p0, p1, p2)
#define MCR_REP_384(macro, p0, p1, p2) MCR_REP_383(macro, p0, p1, p2) macro(384, p0, p1, p2)
#define MCR_REP_385(macro, p0, p1, p2) MCR_REP_384(macro, p0, p1, p2) macro(385, p0, p1, p2)
#define MCR_REP_386(macro, p0, p1, p2) MCR_REP_385(macro, p0, p1, p2) macro(386, p0, p1, p2)
#define MCR_REP_387(macro, p0, p1, p2) MCR_REP_386(macro, p0, p1, p2) macro(387, p0, p1, p2)
#define MCR_REP_388(macro, p0, p1, p2) MCR_REP_387(macro, p0, p1, p2) macro(388, p0, p1, p2)
#define MCR_REP_389(macro, p0, p1, p2) MCR_REP_388(macro, p0, p1, p2) macro(389, p0, p1, p2)
#define MCR_REP_390(macro, p0, p1, p2) MCR_REP_389(macro, p0, p1, p2) macro(390, p0, p1, p2)
#define MCR_REP_391(macro, p0, p1, p2) MCR_REP_390(macro, p0, p1, p2) macro(391, p0, p1, p2)
#define MCR_REP_392(macro, p0, p1, p2) MCR_REP_391(macro, p0, p1, p2) macro(392, p0, p1, p2)
#define MCR_REP_393(macro, p0, p1, p2) MCR_REP_392(macro, p0, p1, p2) macro(393, p0, p1, p2)
#define MCR_REP_394(macro, p0, p1, p2) MCR_REP_393(macro, p0, p1, p2) macro(394, p0, p1, p2)
#define MCR_REP_395(macro, p0, p1, p2) MCR_REP_394(macro, p0, p1, p2) macro(395, p0, p1, p2)
#define MCR_REP_396(macro, p0, p1, p2) MCR_REP_395(macro, p0, p1, p2) macro(396, p0, p1, p2)
#define MCR_REP_397(macro, p0, p1, p2) MCR_REP_396(macro, p0, p1, p2) macro(397, p0, p1, p2)
#define MCR_REP_398(macro, p0, p1, p2) MCR_REP_397(macro, p0, p1, p2) macro(398, p0, p1, p2)
#define MCR_REP_399(macro, p0, p1, p2) MCR_REP_398(macro, p0, p1, p2) macro(399, p0, p1, p2)
#define MCR_REP_400(macro, p0, p1, p2) MCR_REP_399(macro, p0, p1, p2) macro(400, p0, p1, p2)
#define MCR_REP_401(macro, p0, p1, p2) MCR_REP_400(macro, p0, p1, p2) macro(401, p0, p1, p2)
#define MCR_REP_402(macro, p0, p1, p2) MCR_REP_401(macro, p0, p1, p2) macro(402, p0, p1, p2)
#define MCR_REP_403(macro, p0, p1, p2) MCR_REP_402(macro, p0, p1, p2) macro(403, p0, p1, p2)
#define MCR_REP_404(macro, p0, p1, p2) MCR_REP_403(macro, p0, p1, p2) macro(404, p0, p1, p2)
#define MCR_REP_405(macro, p0, p1, p2) MCR_REP_404(macro, p0, p1, p2) macro(405, p0, p1, p2)
#define MCR_REP_406(macro, p0, p1, p2) MCR_REP_405(macro, p0, p1, p2) macro(406, p0, p1, p2)
#define MCR_REP_407(macro, p0, p1, p2) MCR_REP_406(macro, p0, p1, p2) macro(407, p0, p1, p2)
#define MCR_REP_408(macro, p0, p1, p2) MCR_REP_407(macro, p0, p1, p2) macro(408, p0, p1, p2)
#define MCR_REP_409(macro, p0, p1, p2) MCR_REP_408(macro, p0, p1, p2) macro(409, p0, p1, p2)
#define MCR_REP_410(macro, p0, p1, p2) MCR_REP_409(macro, p0, p1, p2) macro(410, p0, p1, p2)
#define MCR_REP_411(macro, p0, p1, p2) MCR_REP_410(macro, p0, p1, p2) macro(411, p0, p1, p2)
#define MCR_REP_412(macro, p0, p1, p2) MCR_REP_411(macro, p0, p1, p2) macro(412, p0, p1, p2)
#define MCR_REP_413(macro, p0, p1, p2) MCR_REP_412(macro, p0, p1, p2) macro(413, p0, p1, p2)
#define MCR_REP_414(macro, p0, p1, p2) MCR_REP_413(macro, p0, p1, p2) macro(414, p0, p1, p2)
#define MCR_REP_415(macro, p0, p1, p2) MCR_REP_414(macro, p0, p1, p2) macro(415, p0, p1, p2)
#define MCR_REP_416(macro, p0, p1, p2) MCR_REP_415(macro, p0, p1, p2) macro(416, p0, p1, p2)
#define MCR_REP_417(macro, p0, p1, p2) MCR_REP_416(macro, p0, p1, p2) macro(417, p0, p1, p2)
#define MCR_REP_418(macro, p0, p1, p2) MCR_REP_417(macro, p0, p1, p2) macro(418, p0, p1, p2)
#define MCR_REP_419(macro, p0, p1, p2) MCR_REP_418(macro, p0, p1, p2) macro(419, p0, p1, p2)
#define MCR_REP_420(macro, p0, p1, p2) MCR_REP_419(macro, p0, p1, p2) macro(420, p0, p1, p2)
#define MCR_REP_421(macro, p0, p1, p2) MCR_REP_420(macro, p0, p1, p2) macro(421, p0, p1, p2)
#define MCR_REP_422(macro, p0, p1, p2) MCR_REP_421(macro, p0, p1, p2) macro(422, p0, p1, p2)
#define MCR_REP_423(macro, p0, p1, p2) MCR_REP_422(macro, p0, p1, p2) macro(423, p0, p1, p2)
#define MCR_REP_424(macro, p0, p1, p2) MCR_REP_423(macro, p0, p1, p2) macro(424, p0, p1, p2)
#define MCR_REP_425(macro, p0, p1, p2) MCR_REP_424(macro, p0, p1, p2) macro(425, p0, p1, p2)
#define MCR_REP_426(macro, p0, p1, p2) MCR_REP_425(macro, p0, p1, p2) macro(426, p0, p1, p2)
#define MCR_REP_427(macro, p0, p1, p2) MCR_REP_426(macro, p0, p1, p2) macro(427, p0, p1, p2)
#define MCR_REP_428(macro, p0, p1, p2) MCR_REP_427(macro, p0, p1, p2) macro(428, p0, p1, p2)
#define MCR_REP_429(macro, p0, p1, p2) MCR_REP_428(macro, p0, p1, p2) macro(429, p0, p1, p2)
#define MCR_REP_430(macro, p0, p1, p2) MCR_REP_429(macro, p0, p1, p2) macro(430, p0, p1, p2)
#define MCR_REP_431(macro, p0, p1, p2) MCR_REP_430(macro, p0, p1, p2) macro(431, p0, p1, p2)
#define MCR_REP_432(macro, p0, p1, p2) MCR_REP_431(macro, p0, p1, p2) macro(432, p0, p1, p2)
#define MCR_REP_433(macro, p0, p1, p2) MCR_REP_432(macro, p0, p1, p2) macro(433, p0, p1, p2)
#define MCR_REP_434(macro, p0, p1, p2) MCR_REP_433(macro, p0, p1, p2) macro(434, p0, p1, p2)
#define MCR_REP_435(macro, p0, p1, p2) MCR_REP_434(macro, p0, p1, p2) macro(435, p0, p1, p2)
#define MCR_REP_436(macro, p0, p1, p2) MCR_REP_435(macro, p0, p1, p2) macro(436, p0, p1, p2)
#define MCR_REP_437(macro, p0, p1, p2) MCR_REP_436(macro, p0, p1, p2) macro(437, p0, p1, p2)
#define MCR_REP_438(macro, p0, p1, p2) MCR_REP_437(macro, p0, p1, p2) macro(438, p0, p1, p2)
#define MCR_REP_439(macro, p0, p1, p2) MCR_REP_438(macro, p0, p1, p2) macro(439, p0, p1, p2)
#define MCR_REP_440(macro, p0, p1, p2) MCR_REP_439(macro, p0, p1, p2) macro(440, p0, p1, p2)
#define MCR_REP_441(macro, p0, p1, p2) MCR_REP_440(macro, p0, p1, p2) macro(441, p0, p1, p2)
#define MCR_REP_442(macro, p0, p1, p2) MCR_REP_441(macro, p0, p1, p2) macro(442, p0, p1, p2)
#define MCR_REP_443(macro, p0, p1, p2) MCR_REP_442(macro, p0, p1, p2) macro(443, p0, p1, p2)
#define MCR_REP_444(macro, p0, p1, p2) MCR_REP_443(macro, p0, p1, p2) macro(444, p0, p1, p2)
#define MCR_REP_445(macro, p0, p1, p2) MCR_REP_444(macro, p0, p1, p2) macro(445, p0, p1, p2)
#define MCR_REP_446(macro, p0, p1, p2) MCR_REP_445(macro, p0, p1, p2) macro(446, p0, p1, p2)
#define MCR_REP_447(macro, p0, p1, p2) MCR_REP_446(macro, p0, p1, p2) macro(447, p0, p1, p2)
#define MCR_REP_448(macro, p0, p1, p2) MCR_REP_447(macro, p0, p1, p2) macro(448, p0, p1, p2)
#define MCR_REP_449(macro, p0, p1, p2) MCR_REP_448(macro, p0, p1, p2) macro(449, p0, p1, p2)
#define MCR_REP_450(macro, p0, p1, p2) MCR_REP_449(macro, p0, p1, p2) macro(450, p0, p1, p2)
#define MCR_REP_451(macro, p0, p1, p2) MCR_REP_450(macro, p0, p1, p2) macro(451, p0, p1, p2)
#define MCR_REP_452(macro, p0, p1, p2) MCR_REP_451(macro, p0, p1, p2) macro(452, p0, p1, p2)
#define MCR_REP_453(macro, p0, p1, p2) MCR_REP_452(macro, p0, p1, p2) macro(453, p0, p1, p2)
#define MCR_REP_454(macro, p0, p1, p2) MCR_REP_453(macro, p0, p1, p2) macro(454, p0, p1, p2)
#define MCR_REP_455(macro, p0, p1, p2) MCR_REP_454(macro, p0, p1, p2) macro(455, p0, p1, p2)
#define MCR_REP_456(macro, p0, p1, p2) MCR_REP_455(macro, p0, p1, p2) macro(456, p0, p1, p2)
#define MCR_REP_457(macro, p0, p1, p2) MCR_REP_456(macro, p0, p1, p2) macro(457, p0, p1, p2)
#define MCR_REP_458(macro, p0, p1, p2) MCR_REP_457(macro, p0, p1, p2) macro(458, p0, p1, p2)
#define MCR_REP_459(macro, p0, p1, p2) MCR_REP_458(macro, p0, p1, p2) macro(459, p0, p1, p2)
#define MCR_REP_460(macro, p0, p1, p2) MCR_REP_459(macro, p0, p1, p2) macro(460, p0, p1, p2)
#define MCR_REP_461(macro, p0, p1, p2) MCR_REP_460(macro, p0, p1, p2) macro(461, p0, p1, p2)
#define MCR_REP_462(macro, p0, p1, p2) MCR_REP_461(macro, p0, p1, p2) macro(462, p0, p1, p2)
#define MCR_REP_463(macro, p0, p1, p2) MCR_REP_462(macro, p0, p1, p2) macro(463, p0, p1, p2)
#define MCR_REP_464(macro, p0, p1, p2) MCR_REP_463(macro, p0, p1, p2) macro(464, p0, p1, p2)
#define MCR_REP_465(macro, p0, p1, p2) MCR_REP_464(macro, p0, p1, p2) macro(465, p0, p1, p2)
#define MCR_REP_466(macro, p0, p1, p2) MCR_REP_465(macro, p0, p1, p2) macro(466, p0, p1, p2)
#define MCR_REP_467(macro, p0, p1, p2) MCR_REP_466(macro, p0, p1, p2) macro(467, p0, p1, p2)
#define MCR_REP_468(macro, p0, p1, p2) MCR_REP_467(macro, p0, p1, p2) macro(468, p0, p1, p2)
#define MCR_REP_469(macro, p0, p1, p2) MCR_REP_468(macro, p0, p1, p2) macro(469, p0, p1, p2)
#define MCR_REP_470(macro, p0, p1, p2) MCR_REP_469(macro, p0, p1, p2) macro(470, p0, p1, p2)
#define MCR_REP_471(macro, p0, p1, p2) MCR_REP_470(macro, p0, p1, p2) macro(471, p0, p1, p2)
#define MCR_REP_472(macro, p0, p1, p2) MCR_REP_471(macro, p0, p1, p2) macro(472, p0, p1, p2)
#define MCR_REP_473(macro, p0, p1, p2) MCR_REP_472(macro, p0, p1, p2) macro(473, p0, p1, p2)
#define MCR_REP_474(macro, p0, p1, p2) MCR_REP_473(macro, p0, p1, p2) macro(474, p0, p1, p2)
#define MCR_REP_475(macro, p0, p1, p2) MCR_REP_474(macro, p0, p1, p2) macro(475, p0, p1, p2)
#define MCR_REP_476(macro, p0, p1, p2) MCR_REP_475(macro, p0, p1, p2) macro(476, p0, p1, p2)
#define MCR_REP_477(macro, p0, p1, p2) MCR_REP_476(macro, p0, p1, p2) macro(477, p0, p1, p2)
#define MCR_REP_478(macro, p0, p1, p2) MCR_REP_477(macro, p0, p1, p2) macro(478, p0, p1, p2)
#define MCR_REP_479(macro, p0, p1, p2) MCR_REP_478(macro, p0, p1, p2) macro(479, p0, p1, p2)
#define MCR_REP_480(macro, p0, p1, p2) MCR_REP_479(macro, p0, p1, p2) macro(480, p0, p1, p2)
#define MCR_REP_481(macro, p0, p1, p2) MCR_REP_480(macro, p0, p1, p2) macro(481, p0, p1, p2)
#define MCR_REP_482(macro, p0, p1, p2) MCR_REP_481(macro, p0, p1, p2) macro(482, p0, p1, p2)
#define MCR_REP_483(macro, p0, p1, p2) MCR_REP_482(macro, p0, p1, p2) macro(483, p0, p1, p2)
#define MCR_REP_484(macro, p0, p1, p2) MCR_REP_483(macro, p0, p1, p2) macro(484, p0, p1, p2)
#define MCR_REP_485(macro, p0, p1, p2) MCR_REP_484(macro, p0, p1, p2) macro(485, p0, p1, p2)
#define MCR_REP_486(macro, p0, p1, p2) MCR_REP_485(macro, p0, p1, p2) macro(486, p0, p1, p2)
#define MCR_REP_487(macro, p0, p1, p2) MCR_REP_486(macro, p0, p1, p2) macro(487, p0, p1, p2)
#define MCR_REP_488(macro, p0, p1, p2) MCR_REP_487(macro, p0, p1, p2) macro(488, p0, p1, p2)
#define MCR_REP_489(macro, p0, p1, p2) MCR_REP_488(macro, p0, p1, p2) macro(489, p0, p1, p2)
#define MCR_REP_490(macro, p0, p1, p2) MCR_REP_489(macro, p0, p1, p2) macro(490, p0, p1, p2)
#define MCR_REP_491(macro, p0, p1, p2) MCR_REP_490(macro, p0, p1, p2) macro(491, p0, p1, p2)
#define MCR_REP_492(macro, p0, p1, p2) MCR_REP_491(macro, p0, p1, p2) macro(492, p0, p1, p2)
#define MCR_REP_493(macro, p0, p1, p2) MCR_REP_492(macro, p0, p1, p2) macro(493, p0, p1, p2)
#define MCR_REP_494(macro, p0, p1, p2) MCR_REP_493(macro, p0, p1, p2) macro(494, p0, p1, p2)
#define MCR_REP_495(macro, p0, p1, p2) MCR_REP_494(macro, p0, p1, p2) macro(495, p0, p1, p2)
#define MCR_REP_496(macro, p0, p1, p2) MCR_REP_495(macro, p0, p1, p2) macro(496, p0, p1, p2)
#define MCR_REP_497(macro, p0, p1, p2) MCR_REP_496(macro, p0, p1, p2) macro(497, p0, p1, p2)
#define MCR_REP_498(macro, p0, p1, p2) MCR_REP_497(macro, p0, p1, p2) macro(498, p0, p1, p2)
#define MCR_REP_499(macro, p0, p1, p2) MCR_REP_498(macro, p0, p1, p2) macro(499, p0, p1, p2)
#define MCR_REP_500(macro, p0, p1, p2) MCR_REP_499(macro, p0, p1, p2) macro(500, p0, p1, p2)
#define MCR_REP_501(macro, p0, p1, p2) MCR_REP_500(macro, p0, p1, p2) macro(501, p0, p1, p2)
#define MCR_REP_502(macro, p0, p1, p2) MCR_REP_501(macro, p0, p1, p2) macro(502, p0, p1, p2)
#define MCR_REP_503(macro, p0, p1, p2) MCR_REP_502(macro, p0, p1, p2) macro(503, p0, p1, p2)
#define MCR_REP_504(macro, p0, p1, p2) MCR_REP_503(macro, p0, p1, p2) macro(504, p0, p1, p2)
#define MCR_REP_505(macro, p0, p1, p2) MCR_REP_504(macro, p0, p1, p2) macro(505, p0, p1, p2)
#define MCR_REP_506(macro, p0, p1, p2) MCR_REP_505(macro, p0, p1, p2) macro(506, p0, p1, p2)
#define MCR_REP_507(macro, p0, p1, p2) MCR_REP_506(macro, p0, p1, p2) macro(507, p0, p1, p2)
#define MCR_REP_508(macro, p0, p1, p2) MCR_REP_507(macro, p0, p1, p2) macro(508, p0, p1, p2)
#define MCR_REP_509(macro, p0, p1, p2) MCR_REP_508(macro, p0, p1, p2) macro(509, p0, p1, p2)
#define MCR_REP_510(macro, p0, p1, p2) MCR_REP_509(macro, p0, p1, p2) macro(510, p0, p1, p2)
#define MCR_REP_511(macro, p0, p1, p2) MCR_REP_510(macro, p0, p1, p2) macro(511, p0, p1, p2)
#define MCR_REP_512(macro, p0, p1, p2) MCR_REP_511(macro, p0, p1, p2) macro(512, p0, p1, p2)

#define MCR_REP(N, MIDDLE, LAST, p0, p1, p2) MCR_CONCAT(MCR_REP_, MCR_DECR(N))(MIDDLE, p0, p1, p2) LAST(N, p0, p1, p2)

#endif
