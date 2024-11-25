module Main where

inteiros :: [Int]
inteiros = [0,9,2,8,3,7,6,4,5]

comp:: [Int]
comp [] = 0
comp (a:x) = 1 + comp x

resultado :: String
resultado = sign comp

main :: IO()
main = putStrLn "resultado"