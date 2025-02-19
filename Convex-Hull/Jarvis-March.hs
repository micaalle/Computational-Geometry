import Data.List (minimumBy)

data Point = Point { x :: Int, y :: Int } deriving (Show, Eq)

direction :: Point -> Point -> Point -> Int
direction (Point pX pY) (Point qX qY) (Point rX rY) =
    let val = (qY - pY) * (rX - qX) - (qX - pX) * (rY - qY)
    in if val > 0 then 1  -- Counterclockwise
       else if val < 0 then -1  -- Clockwise
       else 0  -- Collinear

-- find the leftmost point
leftMost :: [Point] -> Point
leftMost = minimumBy (\(Point x1 y1) (Point x2 y2) -> compare x1 x2)


convexHull :: [Point] -> [Point]
convexHull points = jarvisMarch points (leftMost points)

-- Jarvis march implementation
jarvisMarch :: [Point] -> Point -> [Point]
jarvisMarch points start = jarvisLoop points start [] where
    -- 
    jarvisLoop :: [Point] -> Point -> [Point] -> [Point]
    jarvisLoop points p hull
        | p == start && not (null hull) = hull  
        | otherwise = jarvisLoop points nextPoint (hull ++ [nextPoint]) 
        where
            nextPoint = nextVertex points p

    -- find the next vertex in the convex hull
    nextVertex :: [Point] -> Point -> Point
    nextVertex points p = foldl1 (selectNext p) (filter (/= p) points)

    -- select the point that is the most counterclockwise relative to p
    selectNext :: Point -> Point -> Point -> Point
    selectNext p q r = if direction p q r == 1 then q else r

-- test case
main :: IO ()
main = do
    let points = [ Point (-50) (-30), Point (-48) (-27), Point (-46) (-25), Point (-44) (-23), Point (-42) (-22), Point (-40) (-20),
               Point (-38) (-18), Point (-36) (-17), Point (-34) (-15), Point (-32) (-13), Point (-30) (-12), Point (-28) (-10),
               Point (-26) (-8), Point (-24) (-6), Point (-22) (-5), Point (-20) (-3), Point (-18) (-1), Point (-16) 0,
               Point (-14) 2, Point (-12) 3, Point (-10) 5, Point (-8) 7, Point (-6) 8, Point (-4) 10,
               Point (-2) 12, Point 0 14, Point 2 16, Point 4 18, Point 6 19, Point 8 21,
               Point 10 22, Point 12 24, Point 14 25, Point 16 27, Point 18 28, Point 20 30,
               Point 22 31, Point 24 33, Point 26 34, Point 28 36, Point 30 37, Point 32 39,
               Point 34 40, Point 36 42, Point 38 43, Point 40 45, Point 42 46, Point 44 48,
               Point 46 49, Point 48 51, Point 50 52, Point 52 54, Point 54 55, Point 56 57,
               Point 58 58, Point 60 60, Point 62 61, Point 64 63, Point 66 64, Point 68 65,
               Point 70 67, Point 72 68, Point 74 70, Point 76 71, Point 78 73, Point 80 74,
               Point 82 76, Point 84 77, Point 86 79, Point 88 80, Point 90 82, Point 92 83,
               Point 94 85, Point 96 86, Point 98 88, Point 100 89, Point 102 91, Point 104 92,
               Point 106 94, Point 108 95, Point 110 97, Point 112 98, Point 114 100, Point 116 101,
               Point 118 103, Point 120 104, Point 122 106, Point 124 107, Point 126 109, Point 128 110,
               Point 130 112, Point 132 113, Point 134 115, Point 136 116, Point 138 118, Point 140 119,
               Point 142 121, Point 144 122, Point 146 124, Point 148 125, Point 150 127, Point 152 128,
               Point 154 130, Point 156 131, Point 158 133, Point 160 134 ]

    let hull = convexHull points
    print hull
