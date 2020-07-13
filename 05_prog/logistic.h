#if defined(__cplusplus)
#define __BEGIN_DECLS  extern "C" {
#define __END_DECLS    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

// ヘッダファイルに必要な宣言，定義など

__BEGIN_DECLS

// プロトタイプ宣言リスト
float logistic_(float *x);

__END_DECLS
