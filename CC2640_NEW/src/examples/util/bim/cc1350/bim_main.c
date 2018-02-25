/******************************************************************************

 @file  bim_main.c

 @brief This module contains the definitions for the main functionality of a
        Boot  Image Manager.

 Group: WCS, BTS
 Target Device: CC2650, CC2640, CC1350

 ******************************************************************************
 
 Copyright (c) 2012-2016, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: ble_sdk_2_02_01_18
 Release Date: 2016-10-26 15:20:04
 *****************************************************************************/

/* -----------------------------------------------------------------------------
 *                                          Includes
 * -----------------------------------------------------------------------------
 */
#include <string.h>
#include "hal_flash.h"
#include "hal_types.h"
#include "hal_board.h"
#include "nvocop.h"
/* -----------------------------------------------------------------------------
 *                                          Constants
 * -----------------------------------------------------------------------------
 */

// As defined in applications.
#define LOAD_IMG_A          0x01
#define LOAD_IMG_B          0x02

#define NV_ID_IMAGE_EXECUTE 0x81

#define BIM_LEDGER_ADDR     0x0001E000

/* -----------------------------------------------------------------------------
 *                                          Typedefs
 * -----------------------------------------------------------------------------
 */

// NV item header structure
typedef struct
{
  uint16 id;
  uint16 len;
} NvItemHdr_t;

/* -----------------------------------------------------------------------------
 *                                       Global Variables
 * -----------------------------------------------------------------------------
 */

// Allocate BIM Ledger page in flash.
#if defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=4096
#pragma location = ".bimLedger"
const uint8 BIM_LEDGER_FLASH[HAL_FLASH_PAGE_SIZE];
#elif defined(__TI_COMPILER_VERSION__)
#pragma location = (0x11000);
const uint8 BIM_LEDGER_FLASH[HAL_FLASH_PAGE_SIZE] = {0x00};
#else
#error "Unknown Compiler! Support for SNV not provided!"
#endif

/* -----------------------------------------------------------------------------
 *                                       Local Variables
 * -----------------------------------------------------------------------------
 */

/*******************************************************************************
 * @fn          main
 *
 * @brief       C-code main function.
 *
 * input parameters
 *
 * None.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 */
void main(void)
{
  uint8_t *pLedgerPg = (uint8_t *)BIM_LEDGER_ADDR;
  uint8_t id = LOAD_IMG_A;
  uint32_t snvHeader;
  
  /*
   * VIMS disabling should not be necessary as this is disabled by default and
   * no application has had a chance to modify its state at this point.
   */
  
  memcpy(&snvHeader, pLedgerPg, sizeof(uint32_t));
  
  // Check SNV header, if uninitialized or erased then jump to image A.
  if (snvHeader == 0x00000000 || snvHeader == 0xFFFFFFFF)
  {
    id = LOAD_IMG_A;
  }
  else // Header is ok, try searching for image execute ID.
  {
    uint16_t offset = 0;
    
    // Find ending offset of SNV, starting from the end.
    for (offset = HAL_FLASH_PAGE_SIZE - HAL_FLASH_WORD_SIZE;
         offset >= HAL_FLASH_WORD_SIZE; offset -= HAL_FLASH_WORD_SIZE)
    {
      uint32_t tmp;
      
      // copy in highest 32 bits of SNV that haven't been checked yet.
      memcpy((uint8_t *)&tmp, (uint8_t *)BIM_LEDGER_ADDR + offset, 
             sizeof(uint32_t));
      
      // if anything other than erased, we have found the last SNV entry header.
      if (tmp != 0xFFFFFFFF)
      {
        break;
      }
    }
    
    // We are adjacent to the header and have found nothing.
    if (offset == HAL_FLASH_WORD_SIZE)
    {
      // ledger page is empty, jump to image A.
      id = LOAD_IMG_A;
    }
    else  // we found an the last SNV entry header.
    {
      // Search for NV ID of the latest Image Execute data: 
      while (offset >= 0x04)
      {
        NvItemHdr_t hdr;
       
        // Read the header.
        memcpy((uint8_t *)&hdr, (uint8_t *)BIM_LEDGER_ADDR + offset, 4);
       
        //  If the header's ID type is for Image Execute data
        if (hdr.id == NV_ID_IMAGE_EXECUTE)
        {
          // Most recent data discovered.
          id = *(pLedgerPg + offset - (hdr.len & ~0x8000));
          
          // Jump to this image.
          break;
        }
        else if (hdr.len & 0x8000)
        {
          // Header length was bad, decrement offset by word size and keep 
          // searching.
          offset -= 4;
        }
        else
        {
          if (hdr.len + 4 <= offset)
          {
            // header length was valid, decrement by header length to reach next
            // header.
            offset -= hdr.len + 4;
          }
          else
          {
            // corruption detected just jump to A and hope it goes away.
            id = LOAD_IMG_A;
            
            // Jump to this image.
            break;
          }
        }
      }
    }
  }
  
  // Check which image to load.
  if (id == LOAD_IMG_A)
  {
    // Load address of label __iar_program_start from the fixed location
    // of the image's reset vector,
    asm(" MOV R0, #0x00D0 ");
    asm(" LDR R1, [R0, #0x4] ");
    
    // Reset the stack pointer,
    asm(" LDR SP, [R0, #0x0] ");
    
    // And jump.
    asm(" BX R1 ");
  }
  else // LOAD_IMG_B
  {
    // Load address of the entry point from the fixed location
    // of the image's reset vector,
#if defined(__IAR_SYSTEMS_ICC__)
    asm(" MOV R0, #0x9000 ");
#else
    asm(" MOV R0, #0x8000 ");
#endif
    asm(" LDR R1, [R0, #0x4] ");
    
    // Reset the stack pointer,
    asm(" LDR SP, [R0, #0x0] ");
    
    // And jump.
    asm(" BX R1 ");    
  }
}


/**************************************************************************************************
*/
