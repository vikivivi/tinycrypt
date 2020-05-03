-- This work is licensed under a Creative Commons
-- Attribution-NonCommercial-ShareAlike 4.0 International License.
-- http://creativecommons.org/licenses/by-nc-sa/4.0

-- Mark D. Aagaard
-- Riham AlTawy
-- Guang Gong
-- Kalikinkar Mandal
-- Raghvendra Rohit
-- Marat Sattarov
-- Nusa Zidaric
-- http://uwaterloo.ca/communications-security-lab/lwc/wage


-- This is a human-readable summary of (and not a substitute for) the license. 
-- You are free to:

--     Share:  copy and redistribute the material in any medium or format
--     Adapt:  remix, transform, and build upon the material

--     The licensor cannot revoke these freedoms as long as you follow
--     the license terms.

-- Under the following terms:

--     Attribution — You must give appropriate credit, provide a link to
--     the license, and indicate if changes were made. You may do so in
--     any reasonable manner, but not in any way that suggests the
--     licensor endorses you or your use.

--     NonCommercial — You may not use the material for commercial
--     purposes.

--     ShareAlike — If you remix, transform, or build upon the material,
--     you must distribute your contributions under the same license as
--     the original.

--     No additional restrictions — You may not apply legal terms or
--     technological measures that legally restrict others from doing
--     anything the license permits.

------------------------------------------
--- dwgp-const_array.vhd for expression
--- WGP(wg, gffe)
--- generated by comsecVHDL package on the fly
------------------------------------------

architecture const_array of dwgp is 

	 type dwgp_table_ty is array( 0 to 2**gf_dim - 1) of gf_elem;	 

	 constant dwgp_table:  dwgp_table_ty := 
 	(gf_elem'("0000000"), 
 	 gf_elem'("0010010"), 
 	 gf_elem'("0001010"), 
 	 gf_elem'("1001011"), 
 	 gf_elem'("1100110"), 
 	 gf_elem'("0001100"), 
 	 gf_elem'("1001000"), 
 	 gf_elem'("1110011"), 
 	 gf_elem'("1111001"), 
 	 gf_elem'("0111110"), 
 	 gf_elem'("1100001"), 
 	 gf_elem'("1010001"), 
 	 gf_elem'("0000001"), 
 	 gf_elem'("0010101"), 
 	 gf_elem'("0010111"), 
 	 gf_elem'("0001110"), 
 	 gf_elem'("1111110"), 
 	 gf_elem'("0110011"), 
 	 gf_elem'("1101000"), 
 	 gf_elem'("0110110"), 
 	 gf_elem'("1000010"), 
 	 gf_elem'("0110101"), 
 	 gf_elem'("0110111"), 
 	 gf_elem'("1011110"), 
 	 gf_elem'("1010011"), 
 	 gf_elem'("1001100"), 
 	 gf_elem'("0111111"), 
 	 gf_elem'("1010100"), 
 	 gf_elem'("1011000"), 
 	 gf_elem'("1101110"), 
 	 gf_elem'("1010110"), 
 	 gf_elem'("0101010"), 
 	 gf_elem'("0011101"), 
 	 gf_elem'("0100101"), 
 	 gf_elem'("1101101"), 
 	 gf_elem'("1100101"), 
 	 gf_elem'("1011011"), 
 	 gf_elem'("1110001"), 
 	 gf_elem'("0101111"), 
 	 gf_elem'("0100000"), 
 	 gf_elem'("0000110"), 
 	 gf_elem'("0011000"), 
 	 gf_elem'("0101001"), 
 	 gf_elem'("0111010"), 
 	 gf_elem'("0001101"), 
 	 gf_elem'("1111010"), 
 	 gf_elem'("1101100"), 
 	 gf_elem'("0011011"), 
 	 gf_elem'("0011001"), 
 	 gf_elem'("1000011"), 
 	 gf_elem'("1110000"), 
 	 gf_elem'("1000001"), 
 	 gf_elem'("1001001"), 
 	 gf_elem'("0100010"), 
 	 gf_elem'("1110111"), 
 	 gf_elem'("1100000"), 
 	 gf_elem'("1001111"), 
 	 gf_elem'("1000101"), 
 	 gf_elem'("1010101"), 
 	 gf_elem'("0000010"), 
 	 gf_elem'("1100011"), 
 	 gf_elem'("1000111"), 
 	 gf_elem'("1110101"), 
 	 gf_elem'("0101101"), 
 	 gf_elem'("1000000"), 
 	 gf_elem'("1000110"), 
 	 gf_elem'("1111101"), 
 	 gf_elem'("1011100"), 
 	 gf_elem'("1111100"), 
 	 gf_elem'("1011001"), 
 	 gf_elem'("0100110"), 
 	 gf_elem'("0001011"), 
 	 gf_elem'("0001001"), 
 	 gf_elem'("0000011"), 
 	 gf_elem'("1010111"), 
 	 gf_elem'("1011101"), 
 	 gf_elem'("0100111"), 
 	 gf_elem'("1111000"), 
 	 gf_elem'("0110000"), 
 	 gf_elem'("0101110"), 
 	 gf_elem'("1000100"), 
 	 gf_elem'("1010010"), 
 	 gf_elem'("0111011"), 
 	 gf_elem'("0001000"), 
 	 gf_elem'("1100111"), 
 	 gf_elem'("0101100"), 
 	 gf_elem'("0000101"), 
 	 gf_elem'("1101011"), 
 	 gf_elem'("0101011"), 
 	 gf_elem'("0011010"), 
 	 gf_elem'("0100001"), 
 	 gf_elem'("0111000"), 
 	 gf_elem'("0000111"), 
 	 gf_elem'("0001111"), 
 	 gf_elem'("1001010"), 
 	 gf_elem'("0010001"), 
 	 gf_elem'("1010000"), 
 	 gf_elem'("1101010"), 
 	 gf_elem'("0101000"), 
 	 gf_elem'("0110001"), 
 	 gf_elem'("0010000"), 
 	 gf_elem'("1001101"), 
 	 gf_elem'("1011111"), 
 	 gf_elem'("1110010"), 
 	 gf_elem'("0111001"), 
 	 gf_elem'("0010110"), 
 	 gf_elem'("1011010"), 
 	 gf_elem'("0010011"), 
 	 gf_elem'("0000100"), 
 	 gf_elem'("0111100"), 
 	 gf_elem'("0110100"), 
 	 gf_elem'("0011111"), 
 	 gf_elem'("1110110"), 
 	 gf_elem'("0011110"), 
 	 gf_elem'("0010100"), 
 	 gf_elem'("0100011"), 
 	 gf_elem'("0011100"), 
 	 gf_elem'("0110010"), 
 	 gf_elem'("1001110"), 
 	 gf_elem'("1111011"), 
 	 gf_elem'("0100100"), 
 	 gf_elem'("1110100"), 
 	 gf_elem'("1111111"), 
 	 gf_elem'("0111101"), 
 	 gf_elem'("1101001"), 
 	 gf_elem'("1100100"), 
 	 gf_elem'("1100010"), 
	 gf_elem'("1101111") 
 ); 


begin

  o_wgp <= dwgp_table( to_integer( unsigned( std_logic_vector( i_x ) ) ) );

end architecture;
