const int FP_Pin = 5;	// パルス（前進）信号(A4)はDO5に接続（960Hz?）
const int RP_Pin = 6;	// パルス（後進）信号(A6)はDO6に接続（960Hz?）
const int HOME_Pin = 8;	// 原点復帰信号(A2)をON・OFFするリレーはDO8に接続

void setup() {
	pinMode( HOME_Pin, OUTPUT);
	digitalWrite( HOME_Pin, LOW);

	Serial.begin( 9600 );     // シリアル通信を初期化．通信速度9600bps
	Serial.println( "Hello Arduino!" );   // 最初に1回だけメッセージを表示する
}

void loop() {

	char key; // 受信文字用変数の宣言

	// 受信データがあれば処理を行う
	if ( Serial.available() ) {	// 受信データの存在判定
		key = Serial.read();	// 1文字読む
		Serial.write( key );	// 受信文字エコーバック

		// 受信文字によって動作を変える
		switch( key ){
			case 'f':	// 前進指令（Front）
				analogWrite( FP_Pin, 128 ); // パルス数で速度を指定するため，デューティ比はどれでも同じ？
				delay(1000);
				break;
			case 'r':	// 後進指令（Rear）
				analogWrite( RP_Pin, 128 );
				delay(1000);
				break;
			case '0':	// 原点復帰
				digitalWrite( HOME_Pin, HIGH); // DC24VをHOMEピン（A2）に流すリレーをオン
				delay(100);
				break;
		}
		analogWrite( FP_Pin, 0 );
		analogWrite( RP_Pin, 0 );
		digitalWrite( HOME_Pin, LOW);
	}
	delay(10);
}
