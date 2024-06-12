#include "Decryptor.h"

// 
Decryptor::Decryptor()
{

}
// decrypts a block (pilfered from ida)
// 
DWORD DecryptBlock(PBYTE pKey, PBYTE pData, PBYTE pBuff)
{
	unsigned int v3 = *(DWORD*)(pData + 8);
	unsigned int v4 = v3;
	unsigned int v5 = *(DWORD*)pData;
	unsigned int v6 = *(DWORD*)(pData + 4);
	unsigned int v7 = *(DWORD*)(pData + 12);
	v3 = __ROL4__(v3, 8);
	v4 = __ROR4__(v4, 8);
	unsigned int v8 = (int)pKey;
	unsigned int v9 = v3 & 0xFF00FF | v4 & 0xFF00FF00;
	unsigned int v10 = v7;
	v7 = __ROL4__(v7, 8);
	v10 = __ROR4__(v10, 8);
	unsigned int v11 = v9;
	unsigned int v12 = v9 ^ *(DWORD*)(pKey + 0x8C);
	unsigned int v125 = v7 & 0xFF00FF | v10 & 0xFF00FF00;
	unsigned int v13 = v125 ^ v12 ^ *(DWORD*)(pKey + 0x90);
	unsigned int v14 = dword_AF8C00[(unsigned __int8)(v125 ^ v12 ^ *(BYTE*)(pKey + 0x90))] ^ dword_AF9000[BYTE1(v13)] ^ dword_AF9400[(unsigned __int8)((v125 ^ v12 ^ *(DWORD*)(pKey + 0x90)) >> 16)] ^ dword_AF9800[(v125 ^ v12 ^ *(DWORD*)(pKey + 0x90)) >> 24];
	unsigned int v15 = v14 + v12;
	unsigned int v16 = dword_AF8C00[(unsigned __int8)v15] ^ dword_AF9000[BYTE1(v15)] ^ dword_AF9400[(unsigned __int8)(v15 >> 16)] ^ dword_AF9800[v15 >> 24];
	unsigned int v17 = __ROR4__(v5, 8);
	v5 = __ROL4__(v5, 8);
	unsigned int v18 = dword_AF8C00[(unsigned __int8)(v16 + v14)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v16 + v14) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v16 + v14) >> 16)] ^ dword_AF9800[(unsigned int)(v16 + v14) >> 24];
	unsigned int v19 = (v18 + v16) ^ (v5 & 0xFF00FF | v17 & 0xFF00FF00);
	unsigned int v20 = __ROR4__(v6, 8);
	v6 = __ROL4__(v6, 8);
	unsigned int v21 = v18 ^ (v6 & 0xFF00FF | v20 & 0xFF00FF00);
	unsigned int v22 = v19 ^ *(DWORD*)(v8 + 0x84);
	unsigned int v23 = dword_AF8C00[(unsigned __int8)(v21 ^ v22 ^ *(BYTE*)(v8 + 0x88))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v21 ^ v22 ^ *(WORD*)(v8 + 0x88)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v21 ^ v22 ^ *(DWORD*)(v8 + 0x88)) >> 16)] ^ dword_AF9800[(v21 ^ v22 ^ *(DWORD*)(v8 + 0x88)) >> 24];
	unsigned int v24 = v23 + v22;
	unsigned int v25 = dword_AF8C00[(unsigned __int8)v24] ^ dword_AF9000[BYTE1(v24)] ^ dword_AF9400[(unsigned __int8)(v24 >> 16)] ^ dword_AF9800[v24 >> 24];
	unsigned int v26 = dword_AF8C00[(unsigned __int8)(v25 + v23)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v25 + v23) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v25 + v23) >> 16)] ^ dword_AF9800[(unsigned int)(v25 + v23) >> 24];
	unsigned int v126 = v26 ^ v125;
	unsigned int v27 = (v26 + v25) ^ v11;
	unsigned int v28 = v27 ^ *(DWORD*)(v8 + 0x7C);
	unsigned int v29 = dword_AF8C00[(unsigned __int8)(v126 ^ v28 ^ *(BYTE*)(v8 + 128))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v126 ^ v28 ^ *(WORD*)(v8 + 128)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v126 ^ (unsigned int)v28 ^ *(DWORD*)(v8 + 128)) >> 16)] ^ dword_AF9800[(v126 ^ (unsigned int)v28 ^ *(DWORD*)(v8 + 128)) >> 24];
	unsigned int v30 = v29 + v28;
	unsigned int v31 = dword_AF8C00[(unsigned __int8)v30] ^ dword_AF9000[BYTE1(v30)] ^ dword_AF9400[(unsigned __int8)(v30 >> 16)] ^ dword_AF9800[v30 >> 24];
	unsigned int v32 = dword_AF8C00[(unsigned __int8)(v31 + v29)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v31 + v29) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v31 + v29) >> 16)] ^ dword_AF9800[(unsigned int)(v31 + v29) >> 24];
	unsigned int v33 = v32 ^ v21;
	unsigned int v34 = (v32 + v31) ^ v19;
	unsigned int v35 = v34 ^ *(DWORD*)(v8 + 116);
	unsigned int v36 = dword_AF8C00[(unsigned __int8)(v33 ^ v35 ^ *(BYTE*)(v8 + 120))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v33 ^ v35 ^ *(WORD*)(v8 + 120)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v33 ^ (unsigned int)v35 ^ *(DWORD*)(v8 + 120)) >> 16)] ^ dword_AF9800[(v33 ^ (unsigned int)v35 ^ *(DWORD*)(v8 + 120)) >> 24];
	unsigned int v37 = v36 + v35;
	unsigned int v38 = dword_AF8C00[(unsigned __int8)v37] ^ dword_AF9000[BYTE1(v37)] ^ dword_AF9400[(unsigned __int8)(v37 >> 16)] ^ dword_AF9800[v37 >> 24];
	unsigned int v39 = dword_AF8C00[(unsigned __int8)(v38 + v36)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v38 + v36) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v38 + v36) >> 16)] ^ dword_AF9800[(unsigned int)(v38 + v36) >> 24];
	unsigned int v127 = v39 ^ v126;
	unsigned int v40 = (v39 + v38) ^ v27;
	unsigned int v41 = v40 ^ *(DWORD*)(v8 + 108);
	unsigned int v42 = dword_AF8C00[(unsigned __int8)(v127 ^ v41 ^ *(BYTE*)(v8 + 112))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v127 ^ v41 ^ *(WORD*)(v8 + 112)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v127 ^ (unsigned int)v41 ^ *(DWORD*)(v8 + 112)) >> 16)] ^ dword_AF9800[(v127 ^ (unsigned int)v41 ^ *(DWORD*)(v8 + 112)) >> 24];
	unsigned int v43 = v42 + v41;
	unsigned int v44 = dword_AF8C00[(unsigned __int8)v43] ^ dword_AF9000[BYTE1(v43)] ^ dword_AF9400[(unsigned __int8)(v43 >> 16)] ^ dword_AF9800[v43 >> 24];
	unsigned int v45 = dword_AF8C00[(unsigned __int8)(v44 + v42)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v44 + v42) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v44 + v42) >> 16)] ^ dword_AF9800[(unsigned int)(v44 + v42) >> 24];
	unsigned int v46 = v45 ^ v33;
	unsigned int v47 = (v45 + v44) ^ v34;
	unsigned int v48 = v47 ^ *(DWORD*)(v8 + 100);
	unsigned int v49 = dword_AF8C00[(unsigned __int8)(v46 ^ v48 ^ *(BYTE*)(v8 + 104))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v46 ^ v48 ^ *(WORD*)(v8 + 104)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v46 ^ (unsigned int)v48 ^ *(DWORD*)(v8 + 104)) >> 16)] ^ dword_AF9800[(v46 ^ (unsigned int)v48 ^ *(DWORD*)(v8 + 104)) >> 24];
	unsigned int v50 = v49 + v48;
	unsigned int v51 = dword_AF8C00[(unsigned __int8)v50] ^ dword_AF9000[BYTE1(v50)] ^ dword_AF9400[(unsigned __int8)(v50 >> 16)] ^ dword_AF9800[v50 >> 24];
	unsigned int v52 = dword_AF8C00[(unsigned __int8)(v51 + v49)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v51 + v49) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v51 + v49) >> 16)] ^ dword_AF9800[(unsigned int)(v51 + v49) >> 24];
	unsigned int v128 = v52 ^ v127;
	unsigned int v53 = (v52 + v51) ^ v40;
	unsigned int v54 = v53 ^ *(DWORD*)(v8 + 92);
	unsigned int v55 = dword_AF8C00[(unsigned __int8)(v128 ^ v54 ^ *(BYTE*)(v8 + 96))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v128 ^ v54 ^ *(WORD*)(v8 + 96)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v128 ^ (unsigned int)v54 ^ *(DWORD*)(v8 + 96)) >> 16)] ^ dword_AF9800[(v128 ^ (unsigned int)v54 ^ *(DWORD*)(v8 + 96)) >> 24];
	unsigned int v56 = v55 + v54;
	unsigned int v57 = dword_AF8C00[(unsigned __int8)v56] ^ dword_AF9000[BYTE1(v56)] ^ dword_AF9400[(unsigned __int8)(v56 >> 16)] ^ dword_AF9800[v56 >> 24];
	unsigned int v58 = dword_AF8C00[(unsigned __int8)(v57 + v55)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v57 + v55) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v57 + v55) >> 16)] ^ dword_AF9800[(unsigned int)(v57 + v55) >> 24];
	unsigned int v59 = (v58 + v57) ^ v47;
	unsigned int v60 = v58 ^ v46;
	unsigned int v61 = v59 ^ *(DWORD*)(v8 + 84);
	unsigned int v62 = dword_AF8C00[(unsigned __int8)(v60 ^ v61 ^ *(BYTE*)(v8 + 88))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v60 ^ v61 ^ *(WORD*)(v8 + 88)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v60 ^ (unsigned int)v61 ^ *(DWORD*)(v8 + 88)) >> 16)] ^ dword_AF9800[(v60 ^ (unsigned int)v61 ^ *(DWORD*)(v8 + 88)) >> 24];
	unsigned int v63 = v62 + v61;
	unsigned int v64 = dword_AF8C00[(unsigned __int8)v63] ^ dword_AF9000[BYTE1(v63)] ^ dword_AF9400[(unsigned __int8)(v63 >> 16)] ^ dword_AF9800[v63 >> 24];
	unsigned int v65 = dword_AF8C00[(unsigned __int8)(v64 + v62)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v64 + v62) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v64 + v62) >> 16)] ^ dword_AF9800[(unsigned int)(v64 + v62) >> 24];
	unsigned int v129 = v65 ^ v128;
	unsigned int v66 = (v65 + v64) ^ v53;
	unsigned int v67 = v66 ^ *(DWORD*)(v8 + 76);
	unsigned int v68 = dword_AF8C00[(unsigned __int8)(v129 ^ v67 ^ *(BYTE*)(v8 + 80))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v129 ^ v67 ^ *(WORD*)(v8 + 80)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v129 ^ (unsigned int)v67 ^ *(DWORD*)(v8 + 80)) >> 16)] ^ dword_AF9800[(v129 ^ (unsigned int)v67 ^ *(DWORD*)(v8 + 80)) >> 24];
	unsigned int v69 = v68 + v67;
	unsigned int v70 = dword_AF8C00[(unsigned __int8)v69] ^ dword_AF9000[BYTE1(v69)] ^ dword_AF9400[(unsigned __int8)(v69 >> 16)] ^ dword_AF9800[v69 >> 24];
	unsigned int v71 = dword_AF8C00[(unsigned __int8)(v70 + v68)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v70 + v68) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v70 + v68) >> 16)] ^ dword_AF9800[(unsigned int)(v70 + v68) >> 24];
	unsigned int v72 = v71 ^ v60;
	unsigned int v73 = (v71 + v70) ^ v59;
	unsigned int v74 = v73 ^ *(DWORD*)(v8 + 68);
	unsigned int v75 = dword_AF8C00[(unsigned __int8)(v72 ^ v74 ^ *(BYTE*)(v8 + 72))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v72 ^ v74 ^ *(WORD*)(v8 + 72)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v72 ^ (unsigned int)v74 ^ *(DWORD*)(v8 + 72)) >> 16)] ^ dword_AF9800[(v72 ^ (unsigned int)v74 ^ *(DWORD*)(v8 + 72)) >> 24];
	unsigned int v76 = v75 + v74;
	unsigned int v77 = dword_AF8C00[(unsigned __int8)v76] ^ dword_AF9000[BYTE1(v76)] ^ dword_AF9400[(unsigned __int8)(v76 >> 16)] ^ dword_AF9800[v76 >> 24];
	unsigned int v78 = dword_AF8C00[(unsigned __int8)(v77 + v75)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v77 + v75) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v77 + v75) >> 16)] ^ dword_AF9800[(unsigned int)(v77 + v75) >> 24];
	unsigned int v130 = v78 ^ v129;
	unsigned int v79 = (v78 + v77) ^ v66;
	unsigned int v80 = v79 ^ *(DWORD*)(v8 + 60);
	unsigned int v81 = dword_AF8C00[(unsigned __int8)(v130 ^ v80 ^ *(BYTE*)(v8 + 64))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v130 ^ v80 ^ *(WORD*)(v8 + 64)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v130 ^ (unsigned int)v80 ^ *(DWORD*)(v8 + 64)) >> 16)] ^ dword_AF9800[(v130 ^ (unsigned int)v80 ^ *(DWORD*)(v8 + 64)) >> 24];
	unsigned int v82 = v81 + v80;
	unsigned int v83 = dword_AF8C00[(unsigned __int8)v82] ^ dword_AF9000[BYTE1(v82)] ^ dword_AF9400[(unsigned __int8)(v82 >> 16)] ^ dword_AF9800[v82 >> 24];
	unsigned int v84 = dword_AF8C00[(unsigned __int8)(v83 + v81)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v83 + v81) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v83 + v81) >> 16)] ^ dword_AF9800[(unsigned int)(v83 + v81) >> 24];
	unsigned int v85 = v84 ^ v72;
	unsigned int v86 = (v84 + v83) ^ v73;
	unsigned int v87 = v86 ^ *(DWORD*)(v8 + 52);
	unsigned int v88 = dword_AF8C00[(unsigned __int8)(v85 ^ v87 ^ *(BYTE*)(v8 + 56))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v85 ^ v87 ^ *(WORD*)(v8 + 56)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v85 ^ (unsigned int)v87 ^ *(DWORD*)(v8 + 56)) >> 16)] ^ dword_AF9800[(v85 ^ (unsigned int)v87 ^ *(DWORD*)(v8 + 56)) >> 24];
	unsigned int v89 = v88 + v87;
	unsigned int v90 = dword_AF8C00[(unsigned __int8)v89] ^ dword_AF9000[BYTE1(v89)] ^ dword_AF9400[(unsigned __int8)(v89 >> 16)] ^ dword_AF9800[v89 >> 24];
	unsigned int v91 = dword_AF8C00[(unsigned __int8)(v90 + v88)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v90 + v88) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v90 + v88) >> 16)] ^ dword_AF9800[(unsigned int)(v90 + v88) >> 24];
	unsigned int v131 = v91 ^ v130;
	unsigned int v92 = (v91 + v90) ^ v79;
	unsigned int v93 = v92 ^ *(DWORD*)(v8 + 44);
	unsigned int v94 = dword_AF8C00[(unsigned __int8)(v131 ^ v93 ^ *(BYTE*)(v8 + 48))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v131 ^ v93 ^ *(WORD*)(v8 + 48)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v131 ^ (unsigned int)v93 ^ *(DWORD*)(v8 + 48)) >> 16)] ^ dword_AF9800[(v131 ^ (unsigned int)v93 ^ *(DWORD*)(v8 + 48)) >> 24];
	unsigned int v95 = v94 + v93;
	unsigned int v96 = dword_AF8C00[(unsigned __int8)v95] ^ dword_AF9000[BYTE1(v95)] ^ dword_AF9400[(unsigned __int8)(v95 >> 16)] ^ dword_AF9800[v95 >> 24];
	unsigned int v97 = dword_AF8C00[(unsigned __int8)(v96 + v94)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v96 + v94) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v96 + v94) >> 16)] ^ dword_AF9800[(unsigned int)(v96 + v94) >> 24];
	unsigned int v98 = v97 ^ v85;
	unsigned int v99 = (v97 + v96) ^ v86;
	unsigned int v100 = v99 ^ *(DWORD*)(v8 + 36);
	unsigned int v101 = dword_AF8C00[(unsigned __int8)(v98 ^ v100 ^ *(BYTE*)(v8 + 40))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v98 ^ v100 ^ *(WORD*)(v8 + 40)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v98 ^ (unsigned int)v100 ^ *(DWORD*)(v8 + 40)) >> 16)] ^ dword_AF9800[(v98 ^ (unsigned int)v100 ^ *(DWORD*)(v8 + 40)) >> 24];
	unsigned int v102 = v101 + v100;
	unsigned int v103 = dword_AF8C00[(unsigned __int8)v102] ^ dword_AF9000[BYTE1(v102)] ^ dword_AF9400[(unsigned __int8)(v102 >> 16)] ^ dword_AF9800[v102 >> 24];
	unsigned int v104 = dword_AF8C00[(unsigned __int8)(v103 + v101)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v103 + v101) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v103 + v101) >> 16)] ^ dword_AF9800[(unsigned int)(v103 + v101) >> 24];
	unsigned int v132 = v104 ^ v131;
	unsigned int v105 = (v104 + v103) ^ v92;
	unsigned int v106 = v105 ^ *(DWORD*)(v8 + 28);
	unsigned int v107 = dword_AF8C00[(unsigned __int8)(v132 ^ v106 ^ *(BYTE*)(v8 + 32))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v132 ^ v106 ^ *(WORD*)(v8 + 32)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v132 ^ (unsigned int)v106 ^ *(DWORD*)(v8 + 32)) >> 16)] ^ dword_AF9800[(v132 ^ (unsigned int)v106 ^ *(DWORD*)(v8 + 32)) >> 24];
	unsigned int v108 = v107 + v106;
	unsigned int v109 = dword_AF8C00[(unsigned __int8)v108] ^ dword_AF9000[BYTE1(v108)] ^ dword_AF9400[(unsigned __int8)(v108 >> 16)] ^ dword_AF9800[v108 >> 24];
	unsigned int v110 = dword_AF8C00[(unsigned __int8)(v109 + v107)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v109 + v107) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v109 + v107) >> 16)] ^ dword_AF9800[(unsigned int)(v109 + v107) >> 24];
	unsigned int v111 = v110 ^ v98;
	unsigned int v112 = (v110 + v109) ^ v99;
	unsigned int v113 = v112 ^ *(DWORD*)(v8 + 20);
	unsigned int v114 = dword_AF8C00[(unsigned __int8)(v111 ^ v113 ^ *(BYTE*)(v8 + 24))] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v111 ^ v113 ^ *(WORD*)(v8 + 24)) >> 8)] ^ dword_AF9400[(unsigned __int8)((v111 ^ (unsigned int)v113 ^ *(DWORD*)(v8 + 24)) >> 16)] ^ dword_AF9800[(v111 ^ (unsigned int)v113 ^ *(DWORD*)(v8 + 24)) >> 24];
	unsigned int v115 = v114 + v113;
	unsigned int v116 = dword_AF8C00[(unsigned __int8)v115] ^ dword_AF9000[BYTE1(v115)] ^ dword_AF9400[(unsigned __int8)(v115 >> 16)] ^ dword_AF9800[v115 >> 24];
	unsigned int v117 = dword_AF8C00[(unsigned __int8)(v116 + v114)] ^ dword_AF9000[(unsigned __int8)((unsigned __int16)(v116 + v114) >> 8)] ^ dword_AF9400[(unsigned __int8)((unsigned int)(v116 + v114) >> 16)] ^ dword_AF9800[(unsigned int)(v116 + v114) >> 24];
	unsigned int v118 = (v117 + v116) ^ v105;
	unsigned int v119 = v118;
	v118 = __ROL4__(v118, 8);
	v119 = __ROR4__(v119, 8);
	*(DWORD*)pBuff = v118 & 0xFF00FF | v119 & 0xFF00FF00;
	unsigned int v120 = __ROR4__(v117 ^ v132, 8);
	unsigned int v121 = __ROL4__(v117 ^ v132, 8);
	*(DWORD*)(pBuff + 4) = v121 & 0xFF00FF | v120 & 0xFF00FF00;
	unsigned int v122 = __ROR4__(v112, 8);
	v112 = __ROL4__(v112, 8);
	*(DWORD*)(pBuff + 8) = v112 & 0xFF00FF | v122 & 0xFF00FF00;
	unsigned int v123 = v111;
	v111 = __ROL4__(v111, 8);
	v123 = __ROR4__(v123, 8);
	unsigned int result = v111 & 0xFF00FF | v123 & 0xFF00FF00;
	*(DWORD*)(pBuff + 0xC) = result;
	return result;
}

// decrypts the given data buffer via seed
BOOL DecryptData(PDWORD pData, DWORD dwSize, PDWORD pBuff)
{
	// validates the arguments
	if (pData && pBuff)
	{
		// stores the key
		DWORD* pOwKey = (DWORD*)FirstDecryptionBlock;
		// validates the data (that it has atleast 16 blocks)
		if (dwSize >= 16)
		{
			// iterates through the 16 byte blocks
			for (DWORD dwBlocks = dwSize / 16; dwBlocks != 0; dwBlocks--)
			{
				// decrypts the blocks
				DecryptBlock((PBYTE)DecryptionKey, (PBYTE)pData, (PBYTE)pBuff);
				// xors with the key
				pBuff[0] ^= pOwKey[0];
				pBuff[1] ^= pOwKey[1];
				pBuff[2] ^= pOwKey[2];
				pBuff[3] ^= pOwKey[3];
				// sets the ow key pointer as a pointer to the new key
				pOwKey = pData;
				// gets the next block
				pData += 4;
				// gets the next block
				pBuff += 4;
			}
		}
		// function succeeded
		return TRUE;
	}
	// function failed
	return FALSE;
}