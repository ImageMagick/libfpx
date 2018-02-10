/* -*-C-*-
******************************************************************************
*
* File:         huffman.h     
* RCS:          $Header: /ImageMagick/delegates/fpx/jpeg/huffman.h,v 1.2 2000/12/23 22:37:48 bfriesen Exp $
* Description:  builds Huffman encoding table
* Author:       Hugh P. Nguyen
* Created:      Fri Dec  4 11:04:22 1992
* Initial Source Release:     Wed Jan 17 1996
* Language:     C
* Package:      Hewlett-Packard JPEG Encoder/Decoder
*
* Copyright (c) 1999 Digital Imaging Group, Inc.
* For conditions of distribution and use, see copyright notice
* in Flashpix.h
*
******************************************************************************
*/

JPEGEXPORT
void BuildHuffmanTable(unsigned char *bits,
             unsigned char *huffval,
             HUFFMAN_TABLE *table);
