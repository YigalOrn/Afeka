from django.shortcuts import render
from django.shortcuts import get_object_or_404
from django.http import HttpResponseRedirect
from django.core.urlresolvers import reverse
from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from django.contrib.auth import login
from django.db.models import Q
from .models import Message
from django.utils import timezone
from django.http import Http404


# Create your views here.

@login_required
def index(request):
    userLst = User.objects.exclude(pk=request.user.pk).order_by('username')
    context = {'userLst': userLst}
    return render(request, 'ChitChat/index.html', context)


def userRegistration(request):
    if request.method == 'POST':
        """
        I am not sure but, if  UserCreationForm doesnt catch internally POST mismatch and other
        possible violations regarding the tempaering of a POST 'packet'
        there should be a try clause here!!
        """
        form = UserCreationForm(request.POST)
        if form.is_valid():
            user = User.objects.create_user(
                username=request.POST['username'], password=request.POST['password1'])
            login(request, user)
            return HttpResponseRedirect(reverse('index'))
    else:
        form = UserCreationForm()
    return render(request, 'ChitChat/registration/userRegistration.html', {'form': form})


@login_required
def correspondence(request, user_pk):
    user_1, user_2 = get_object_or_404(User, pk=request.user.pk), get_object_or_404(User, pk=user_pk)
    messagesLst = Message.objects.filter(
        Q(sender=user_1, recipient=user_2) | Q(sender=user_2, recipient=user_1)).order_by(
        '-pub_date')
    return render(request, 'ChitChat/correspondence.html',
                  {'messagesLst': messagesLst, 'redirect_user': user_2})


@login_required
def newMessage(request, redirect_user_pk):
    try:
        senderUser = request.user
        recipientUser = User.objects.get(pk=redirect_user_pk)
        newMesage = Message(sender=senderUser, recipient=recipientUser,
                            message=request.POST['correspondence_textarea_form'],
                            pub_date=timezone.now())
    except (KeyError, User.DoesNotExist):
        raise Http404('Error occurred in newMessage: KeyError or User.DoesNotExist')
    else:
        newMesage.save()
        return HttpResponseRedirect(reverse('correspondence', args=(redirect_user_pk,)))
