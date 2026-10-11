#include "common.h"
#include "common_types.h"
#include "PR/os.h"

INCLUDE_ASM("asm/nonmatchings/main/832A0", findModelAnimKeyframeByPhase);

INCLUDE_ASM("asm/nonmatchings/main/832A0", resetModelAnimSlotTable);

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocateModelAnimSlot);

INCLUDE_ASM("asm/nonmatchings/main/832A0", appendAnimHandleAndDescendantsToBuffer);

INCLUDE_ASM("asm/nonmatchings/main/832A0", flattenAnimTreeAndAllocateSlot);

INCLUDE_ASM("asm/nonmatchings/main/832A0", model_animation_offset_convert);

INCLUDE_ASM("asm/nonmatchings/main/832A0", releaseModelAnimSlot);

INCLUDE_ASM("asm/nonmatchings/main/832A0", markModelAnimChannelEntryActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", clearModelAnimChannelEntry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seekModelAnimChannelToTime);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seekAllModelAnimChannelsInSlotToTime);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setModelAnimChannelEntryDuration);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getModelAnimChannelEntryDuration);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setModelAnimSlotCycleDuration);

INCLUDE_ASM("asm/nonmatchings/main/832A0", sampleModelAnimKeyframeVec3);

INCLUDE_ASM("asm/nonmatchings/main/832A0", parseModelAnimType2Entry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", audioSeqMallocZero);

INCLUDE_ASM("asm/nonmatchings/main/832A0", audioSeqFree);

INCLUDE_ASM("asm/nonmatchings/main/832A0", unusedRand);

INCLUDE_ASM("asm/nonmatchings/main/832A0", lookupSineFromAngleTable);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setTrackVoiceTickBudget);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getTrackVoiceTickBudget);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setChannelNoteCell);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setChannelByteParam);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getChannelByteParam);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setChannelByteParamAlt);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getChannelByteParamAlt);

INCLUDE_ASM("asm/nonmatchings/main/832A0", resetChannelStateRecord);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getChannelControllerValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initVoiceModulatorRecords);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecord);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordZero);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordOne);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordTwo);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordThree);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordFour);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordFive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordSix);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordSeven);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecordEight);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableRemoveValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertTaggedValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableRemoveTaggedValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SecondSortedTableInsertValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SecondSortedTableRemoveValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertWidePair);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableRemoveWidePair);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertVoiceRecord);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableRemoveVoiceRecord);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5BucketedTableInsertEntry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5BucketedTableRemoveEntry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", binarySearchWithComparator);

s32 func_main_80085CD8(u8 *a, u8 *b) {
    return *(u16 *)(a + 4) - *(u16 *)(b + 4);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5BucketedTableLookupValue);

s32 compareHalfwordAtOffset8(u8 *a, u8 *b) {
    return *(u16 *)(a + 8) - *(u16 *)(b + 8);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableLookupWidePairRecord);

s32 compareHalfwordAtOffset4_v2(u8 *a, u8 *b) {
    return *(u16 *)(a + 4) - *(u16 *)(b + 4);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SecondSortedTableLookupValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableLookupValue);

s32 compareHalfwordAtOffset4_v3(u8 *a, u8 *b) {
    return *(u16 *)(a + 4) - *(u16 *)(b + 4);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableLookupTaggedValue);

s32 cmpU16ByValue(u8 *a, u8 *b) {
    return *(u16 *)(a + 0) - *(u16 *)(b + 0);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSortedInsertByU16);

INCLUDE_ASM("asm/nonmatchings/main/832A0", freeSynthVoiceFromActiveList);

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocVoiceHandleNode);

INCLUDE_ASM("asm/nonmatchings/main/832A0", resolveVoiceSlotByHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocateSynthVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", stopVoiceByKey);

INCLUDE_ASM("asm/nonmatchings/main/832A0", silenceVoiceSlot);

INCLUDE_ASM("asm/nonmatchings/main/832A0", computeVoiceGlidePitch);

INCLUDE_ASM("asm/nonmatchings/main/832A0", queryVoicePlayPositionByHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", findActiveVoiceByKeyPair);

INCLUDE_ASM("asm/nonmatchings/main/832A0", findVoiceForNote);

INCLUDE_ASM("asm/nonmatchings/main/832A0", startNoteOnVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", applyNoteEventToGroup);

INCLUDE_ASM("asm/nonmatchings/main/832A0", dispatchSequencerNoteEvent);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxNoteEventLockedDispatch);

INCLUDE_ASM("asm/nonmatchings/main/832A0", bsearchFactor5TableByU16Key);

INCLUDE_ASM("asm/nonmatchings/main/832A0", validateVoiceHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSetSequenceParamLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxQuerySequenceLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setVoiceParamByHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setVoiceParamByHandleLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", applyVoiceCmdByHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", applyVoiceCmdByHandleLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceKeyTransposeAcrossChain);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceKeyTransposeLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoicePanVolumeAcrossChain);

INCLUDE_ASM("asm/nonmatchings/main/832A0", safeLookup3DSoundEntry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceParamPairLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceByteParamAcrossChain);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceByteParamLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceParamLockedVariant);

INCLUDE_ASM("asm/nonmatchings/main/832A0", flagVoiceChainForStop);

INCLUDE_ASM("asm/nonmatchings/main/832A0", stopVoiceByHandleLocked);

void shiftChannelStreamLeft8(u32 *p) {
    *p <<= 8;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", computeChannelTempoStepFromTable);

INCLUDE_ASM("asm/nonmatchings/main/832A0", computeChannelWaitDuration);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpWaitTicks);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStopVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpReturnFromGosub);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubLoopCounterFiftyFour);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubLoopCounterThirty);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubModulatorLoop);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubRandomLoop);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosub);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubAltReturnFrame);

s32 clearChannelFieldsAt1Cand20(u8 *ch) {
    *(s32 *)(ch + 0x20) = 0;
    *(s32 *)(ch + 0x1C) = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpLoopRandomCount);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpKeyOnNote);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpKeyOffByNote);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpAddPitchBend);

s32 setChannelProgHalfwordAt28(u8 *ch, u16 *cmd) {
    *(u32 *)(ch + 0x28) = *cmd << 16;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetPitchBendGlide);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpAddKeyByte);

s32 setChannelProgByteAt2E(u8 *ch, u32 *cmd) {
    ch[0x2E] = *cmd >> 8;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStoreGlobalRegister);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setChannelKeyOffsetAt6E);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpPortamentoStartWait);

INCLUDE_ASM("asm/nonmatchings/main/832A0", computeChannelPitchSweepStep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartNoteAbsoluteSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartNoteRelativeSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartNoteTransposedSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpPlaySampleKeymap);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpKeyOff);

s32 setChannelFlag24Bit80(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x80;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetPanSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetProgramTableValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartPitchEnvelope);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSetVoiceAdsrFromTable);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartVibrato);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetVolumeRamp);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetPitchRelativeToNote);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateSoundMacroCurveTable);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroSetVoiceVolume);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroSetupVolumeRamp);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroPlayRandomKeyNote);

s32 soundMacroSetFlagBitVibrato(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x20000;
    return 0;
}

s32 soundMacroSetFlagBitTremolo(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x40000;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroPushEffectEvent);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler40);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler41);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler42);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler43);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler44);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler45);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler46);

INCLUDE_ASM("asm/nonmatchings/main/832A0", refreshVoicePlaybackRate);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroSetPitchTarget);

INCLUDE_ASM("asm/nonmatchings/main/832A0", tickAudioChannel);

INCLUDE_ASM("asm/nonmatchings/main/832A0", tickAllAudioChannels);

INCLUDE_ASM("asm/nonmatchings/main/832A0", tickAudioSequencerFrame);

INCLUDE_ASM("asm/nonmatchings/main/832A0", tickMusyXIfActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", releaseSynthVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", stopVoicesByHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", stopAllSynthVoices);

extern u8 D_main_bss_80148C58[];
u8 getMusyXChannelSlotByte(s32 i) {
    return D_main_bss_80148C58[i & 0xF];
}

extern u8 D_main_bss_80148C58[];
void setMusyXChannelSlotByte(s32 i, u8 v) {
    D_main_bss_80148C58[i & 0xF] = v;
}

extern u8 D_main_bss_801483C8;
void setMusyXVoiceTickGate(u8 arg0) {
    D_main_bss_801483C8 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", dispatchAudioCommand);

INCLUDE_ASM("asm/nonmatchings/main/832A0", playSimpleAudioCmd);

INCLUDE_ASM("asm/nonmatchings/main/832A0", applyMusicOrSfxVolume);

INCLUDE_ASM("asm/nonmatchings/main/832A0", isAudioFaderRampActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setupAudioFaderRamp);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setAudioFaderRampLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setAudioFaderState);

INCLUDE_ASM("asm/nonmatchings/main/832A0", anyAudioSlotActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", resetMusyXEngineState);

INCLUDE_ASM("asm/nonmatchings/main/832A0", clearMusyXSequencerState);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getMusyXStateTableIfActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", syncMusyXIfActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", runMusyXTaskLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initMusyXEngine);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setDisplayMode);

INCLUDE_ASM("asm/nonmatchings/main/832A0", reapplyDisplayMode);

INCLUDE_ASM("asm/nonmatchings/main/832A0", shutdownMusyXEngine);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxNoopStub);

extern u8 gMusyXActiveFlag;
u8 isMusyXActive(void) {
    return gMusyXActiveFlag;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", serviceAudioOutputBuffers);

INCLUDE_ASM("asm/nonmatchings/main/832A0", runAiAudioStreamPlaybackLoop);

INCLUDE_ASM("asm/nonmatchings/main/832A0", buildSongTempoSchedule);

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocateSongChannelArray);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setupSongRenderBuffers);

INCLUDE_ASM("asm/nonmatchings/main/832A0", advanceVolumeFadeEnvelope);

INCLUDE_ASM("asm/nonmatchings/main/832A0", buildSongDecodeBufferRing);

INCLUDE_ASM("asm/nonmatchings/main/832A0", acquireSampleStreamBlock);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initSampleStreamBlockCache);

INCLUDE_ASM("asm/nonmatchings/main/832A0", moveSampleBlockToFront);

INCLUDE_ASM("asm/nonmatchings/main/832A0", recycleSampleStreamBlock);

INCLUDE_ASM("asm/nonmatchings/main/832A0", fillSampleStreamRange);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxRenderVoiceSamples);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxKeyOnVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxMixActiveVoices);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxBuildVoiceCommandList);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSynthFrame);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initN64RspMixer);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initAudioSubsystem);

INCLUDE_ASM("asm/nonmatchings/main/832A0", reapplyAudioConfig);

INCLUDE_ASM("asm/nonmatchings/main/832A0", shutdownAudioEngine);

INCLUDE_ASM("asm/nonmatchings/main/832A0", waitForMusyXAudioTaskDone);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initFactor5Mutex);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5MutexAcquire);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5MutexRelease);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5QueueBlock);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5QueueSignal);

INCLUDE_ASM("asm/nonmatchings/main/832A0", isAudioSlotActive);

s32 audioStubReturnZero(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxInitVoiceFromSample);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxStartVoiceRelease);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxStoreVoiceAdsrParams);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxTriggerVoiceAttack);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxStopVoice);

void noopHandler_80092388(void) {
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSetVoicePitchBend);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setVoiceModulationParams);

INCLUDE_ASM("asm/nonmatchings/main/832A0", stopVoiceMarkRetrigger);

INCLUDE_ASM("asm/nonmatchings/main/832A0", beginVoiceFadeRelease);

INCLUDE_ASM("asm/nonmatchings/main/832A0", deactivateVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", tickAudioBufferUpdate);
