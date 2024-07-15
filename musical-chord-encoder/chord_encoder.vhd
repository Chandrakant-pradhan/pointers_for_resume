library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use ieee.std_logic_textio.all;
use std.textio.all;

entity CHORDEncoder is
    port (
        clk, rst: in std_logic;
        a: in std_logic_vector(7 downto 0);
        data_valid: out std_logic;
        z: out std_logic_vector(7 downto 0)
    );
end entity CHORDEncoder;

architecture behavior of CHORDEncoder is
    
    function my_num(flag : std_logic_vector(7 downto 0)) return integer is
    begin
        case flag is
            when "01000011" => return 0;   -- C
            when "01000100" => return 2;   -- D
            when "01000101" => return 4;   -- E
            when "01000110" => return 5;   -- F
            when "01000111" => return 7;   -- G
            when "01000001" => return 9;   -- A
            when "01000010" => return 11;  -- B 
            when "01100011" => return 11;  -- c
            when "01100100" => return 1;   -- d
            when "01100101" => return 3;   -- e
            when "01100110" => return 4;   -- f
            when "01100111" => return 6;   -- g
            when "01100001" => return 8;   -- a
            when "01100010" => return 10;  -- b 
            when "01110011" => return 29; --s
            when "01101101" => return 30; --m;
            when  "00110111" => return 31; -- 7;
            when "01001101" => return 32; --M;

            when others => return -1;      -- Default case (invalid input)
        end case;
    end function;

    function my_bin(n: integer) return std_logic_vector is
    begin
        case n is
            when 0 => return "01000011";
            when 1 => return "01100100";
            when 2 => return "01000100";
            when 3 => return "01100101";
            when 4 => return "01000101";
            when 5 => return "01000110";
            when 6 => return "01100111";
            when 7 => return "01000111";
            when 8 => return "01100001";
            when 9 => return "01000001";
            when 10 => return "01100010";
            when 11 => return "01000010";
            when 29 => return "01110011";
            when 30 => return "01101101";
            when 31 => return "00110111";
            when 32 => return "01001101";
            when others => return "00000000";
        end case;
    end function;
begin
    process(clk , rst)
        variable f : integer := 0;
        variable temp_value : integer; 
        variable size : integer := 0;
        variable tail : integer := 0;
        variable head : integer := 0;
        type arr is array(0 to 31) of integer;
        variable preprocess : arr;
        variable output : arr;
    begin
    if rising_edge(clk) then
          if(head <= 31 and tail/=head) then
            z <= my_bin(output(tail));
            tail := tail +1 ;
          else
            if(head /= 0) then
            data_valid <= '0';
            end if;
          end if; 

          if(rst = '0') then
            z<="00010001";
            if a /= "00100011" then
                if size < 32 then
                    temp_value := my_num(a); 
                    z <= my_bin(temp_value);
                    preprocess(size) := temp_value; 
                    
                    size := size + 1;
                end if;
            elsif a = "00100011" then
                if size > 0 then
                    temp_value := (preprocess(size - 1) + 1) mod 12; 
                    z <= my_bin(temp_value);
                    preprocess(size - 1) := temp_value; 
                    
                end if;
            end if;
           end if;
         
        elsif(rst = '1') then
            
            if(f < size or f = size) then
                
                if(f+1 < size or f+1 = size) then
                    if((preprocess(f+1) - preprocess(f)) mod 12  = 3) then
                        if(f+2 < size or f+2 = size)then
                            if( (preprocess(f+2) - preprocess(f+1)) mod 12 = 4) then
                                temp_value := preprocess(f);
                                output(head) <= temp_value;
                                head := head+1;
                                temp_value := 30;
                                output(head) <= temp_value;
                                head := head+1;
                                f := f+3;
                            else
                                temp_value := preprocess(f);
                                output(head) <= temp_value;
                                head := head+1;
                                f := f+1;
                            end if;
                        else
                            temp_value := preprocess(f);
                            output(head) <= temp_value;
                            head := head +1;
                            temp_value := preprocess(f+1);
                            output(head) <= temp_value;
                            head := head+1;
                        end if;
                    elsif((preprocess(f+1) - preprocess(f)) mod 12 = 5) then
                        if(f+2 < size or f+2 = size)then
                            if((preprocess(f+2) - preprocess(f+1)) mod 12 = 2) then
                                temp_value := preprocess(f);
                                output(head) <= temp_value;
                                head := head +1 ;
                                temp_value := 29;
                                output(head) <= temp_value;
                                head := head+1;
                                f := f+3;
                            else
                                temp_value := preprocess(f);
                                output(head) <= temp_value;
                                head := head+1;
                                f := f+1;
                            end if;
                        else
                            temp_value := preprocess(f);
                            output(head) <= temp_value;
                            head := head +1;
                            temp_value := preprocess(f+1);
                            output(head) <= temp_value;
                            head := head+1;   
                        end if;
                    elsif((preprocess(f+1) - preprocess(f)) mod 12 = 4) then
                        if(f+2 < size or f+2 = size)then
                            if((preprocess(f+2) - preprocess(f+1)) mod 12 = 3) then
                                if(f+3 < size or f+3 = size) then
                                    if((preprocess(f+3)- preprocess(f+2))mod 12 = 3) then
                                        temp_value := preprocess(f);
                                        output(head) <= temp_value;
                                        head := head +1 ;
                                        temp_value := 31;
                                        output(head) <= temp_value;
                                        head := head+1;
                                        f := f+4;
                                    else
                                        temp_value := preprocess(f);
                                        output(head) <= temp_value;
                                        head := head +1 ;
                                        temp_value := 32;
                                        output(head) <= temp_value;
                                        head := head+1;
                                        f := f+3;
                                    end if;
                                else
                                    temp_value := preprocess(f);
                                    output(head) <= temp_value;
                                    head := head +1 ;
                                    temp_value := 32;
                                    output(head) <= temp_value;
                                    head := head+1;
                                end if;
                            else
                                temp_value := preprocess(f);
                                output(head) <= temp_value;
                                head := head +1;
                                f:= f+1;
                            end if;
                        else
                            temp_value := preprocess(f);
                            output(head) <= temp_value;
                            head := head +1;
                            temp_value := preprocess(f+1);
                            output(head) <= temp_value;
                            head := head+1;
                        end if;
                    else
                        temp_value := preprocess(f);
                        output(head) <= temp_value;
                        head := head+1;
                        f:=f+1;
                    end if;

                else
                    temp_value := preprocess(f);
                    output(head) <= temp_value;
                    head := head+1;
                end if;
            end if;
        
        end if;
    end if;

              
    end process;
    
end architecture behavior;