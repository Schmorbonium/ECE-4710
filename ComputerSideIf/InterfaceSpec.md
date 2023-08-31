<link rel="stylesheet" href="MDstyle.css">

InterBoard Header Byte (Words)
<table>
    <tr>
        <th>7</th>
        <th>6</th>
        <th>5</th>
        <th>4</th>
        <th>3</th>
        <th>2</th>
        <th>1</th>
        <th>0</th>
    </tr>
    <tr>
        <td colspan="4">Attention Bits </td><td colspan="2">Unused</td><td colspan="2">ttl </td>
    </tr>
    <tr>
        <td colspan="3">Data_Len</td><td colspan="5">Message cmd Id</td>
    </tr>
</table>

Computer Interface Header
<table>
    <tr>
        <th>31</th><th>30</th><th>29</th><th>28</th><th>27</th><th>26</th><th>25</th><th>24</th><th>23</th><th>22</th><th>21</th><th>20</th><th>19</th><th>18</th><th>17</th><th>16</th><th>15</th><th>14</th><th>13</th><th>12</th><th>11</th><th>10</th><th>9</th><th>8</th><th>7</th><th>6</th><th>5</th><th>4</th><th>3</th><th>2</th><th>1</th><th>0</th>
    </tr>
    <tr>
        <td colspan="8">Operation(Byte)</td><td colspan="8">Msg Length</td><td colspan="16">CheckSum?</td>
    </tr>
</table>

Operations
|Operation| Value | description|
|-|-|-|
|reset          |0x1|
|SetMem         |0x2|
|GetMem         |0x3|
|OpFailed       |0x4|
|dbSetReg       |0x11|
|dbGetReg       |0x12|
|dbGetFlags     |0x13|
|dbSetPC        |0x14|
|dbPause        |0x15|
|dbStep         |0x16|
|dbNewBP        |0x17|
|dbStep         |0x18|

Computer Interface Header
<table>
    <tr>
        <th>31</th><th>30</th><th>29</th><th>28</th><th>27</th><th>26</th><th>25</th><th>24</th><th>23</th><th>22</th><th>21</th><th>20</th><th>19</th><th>18</th><th>17</th><th>16</th><th>15</th><th>14</th><th>13</th><th>12</th><th>11</th><th>10</th><th>9</th><th>8</th><th>7</th><th>6</th><th>5</th><th>4</th><th>3</th><th>2</th><th>1</th><th>0</th>
    </tr>
    <tr>
        <td colspan="8">Operation(Byte)</td><td colspan="8">Msg Length</td><td colspan="16">CheckSum?</td>
    </tr>
</table>

Computer Interface Header
<table>
    <tr>
        <th>31</th><th>30</th><th>29</th><th>28</th><th>27</th><th>26</th><th>25</th><th>24</th><th>23</th><th>22</th><th>21</th><th>20</th><th>19</th><th>18</th><th>17</th><th>16</th><th>15</th><th>14</th><th>13</th><th>12</th><th>11</th><th>10</th><th>9</th><th>8</th><th>7</th><th>6</th><th>5</th><th>4</th><th>3</th><th>2</th><th>1</th><th>0</th>
    </tr>
    <tr>
        <td colspan="8">Operation(Byte)</td><td colspan="8">Msg Length</td><td colspan="16">CheckSum?</td>
    </tr>
</table>
