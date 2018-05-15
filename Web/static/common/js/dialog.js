const DIALOG_ANIME_TIME = 300 ;
const DIALOG_ANIME_TIME_IMMEDIATELAY = 0 ;

function showDialog(){
    $('#dialog_background').css('display','block');
    $('#dialog_background').fadeOut(DIALOG_ANIME_TIME_IMMEDIATELAY);
    $('#dialog_background').fadeIn(DIALOG_ANIME_TIME);
    $('#dialog_self').animate({
        top : '+=100px',
    },DIALOG_ANIME_TIME_IMMEDIATELAY)
    $('#dialog_self').animate({
        top : '-=100px',
    },DIALOG_ANIME_TIME)
}

function showDialogWithContent(titleStr,contentStr){
    showDialog();
    $('#dialog_title').text(titleStr);
    $('#dialog_content').text(contentStr);
}

function hideDialog(){
    $('#dialog_background').css('display','none');
    $('#dialog_background').fadeIn(DIALOG_ANIME_TIME_IMMEDIATELAY);
    $('#dialog_background').fadeOut(DIALOG_ANIME_TIME);
    $('#dialog_self').animate({
        top : '+=100px',
    },DIALOG_ANIME_TIME);
    $('#dialog_self').animate({
        top : '-=100px',
    },DIALOG_ANIME_TIME_IMMEDIATELAY);
}