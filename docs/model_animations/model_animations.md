# Model Animations

I don't know much about the animation files.
I have the general shape of the data figured out, but the actual meaning of most of the data is beyond me.

The files start with a `u32` that is a count of what I'll call `type1` entries.
Then there's a `u32` that is the offset to the `type1` entries, followed by a zero-word.
This means that the `type1_offset` is always(?) `0x0000000C`.
I also think the `type1_count` is always `1`, but I haven't been thorough in confirming that.

```cpp
struct model_anim_type1 {
    /* 0x00 */ u32 type2_offset;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 type2_count;
}; // size = 0x10

struct model_anim_type2 {
    /* 0x00 */ u32 entry_count;
    /* 0x04 */ u32 flags;
    /* 0x08 */ u32 singlet_offset;
    /* 0x0C */ u32 triplet_offset1; // flags 0x1
    /* 0x10 */ u32 triplet_offset2; // flags 0x2
    /* 0x14 */ u32 quadlet_offset;  // flags 0x4
    /* 0x18 */ u32 triplet_offset3; // flags 0x8
}; // size = 0x1C
```

The various `*_offset` entries in `type2` entries point to lists of sing/trip/quadlet `s16` groups.
Depending on the bits in `flags` the trip/quadlet lists will have either 1 or `entry_count` items.
The singlet list always has `entry_count` entries.
`func_80083468` is a very informative function concerning the trip/quadlet lists.
